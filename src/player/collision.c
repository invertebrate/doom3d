/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/06 19:36:41 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** https://gamedev.stackexchange.com/questions/49956/
** collision-detection-smooth-wall-sliding-no-bounce-effect
*/

/*
static void		nudge_away(t_doom3d *app, t_player *future_player,
									t_3d_object *collider, t_vec3 hit_point)
{
	t_vec3	dist;
	t_vec3	tmp;
	t_vec3	nudge;
	float	player_size;
	int		i;

	if (collider->type == object_type_projectile ||
		collider->type == object_type_path ||
		collider->type == object_type_trigger)
		return ;
	// define limit on when to stop nudge
	ml_vector3_copy(app->player.aabb.size, tmp);
	ml_vector3_mul(tmp, 0.5, tmp);
	tmp[1] = 0;
	player_size = ml_vector3_mag(tmp);
	// define nudge
	ml_vector3_sub(collider->aabb.center, future_player->aabb.center, tmp);
	tmp[1] = 0;
	ml_vector3_normalize(tmp, nudge);
	ml_vector3_mul(nudge, 10, nudge);
	//start nudging
	LOG_TRACE("dist = %f, player_size = %f", ml_vector3_mag(dist), app->unit_size);//test
	ml_vector3_sub(hit_point, future_player->aabb.center, dist);
	i = -1;
	while (ml_vector3_mag(dist) < app->unit_size && ++i < player_size / 10)
	{
		ml_vector3_sub(future_player->pos, nudge, future_player->pos);
		ml_vector3_sub(app->player.pos, nudge, app->player.pos);
		player_update_aabb(future_player);
		ml_vector3_sub(hit_point, future_player->aabb.center, dist);
		LOG_TRACE("nudge vector = {%f, %f, %f}", nudge[0], nudge[1], nudge[2]);//test
		LOG_TRACE("nudge_player_away");
	}
	player_update_aabb(&app->player);
}*/

static void		limit_move_add_by_collision(t_vec3 collision_normal,
					t_vec3 dir_add)
{
	t_vec3		direction_wall_part;

	ml_vector3_normalize(collision_normal, collision_normal);
	ml_vector3_mul(collision_normal,
		ml_vector3_dot(dir_add, collision_normal), direction_wall_part);
	ml_vector3_sub(dir_add, direction_wall_part, dir_add);
}

static void		set_future_player(t_doom3d *app, t_vec3 add,
					t_player *future_player)
{
	t_vec3	new_add;

	ml_vector3_add(add, (t_vec3) {0, -app->player.player_height / 4, 0},
					new_add);
	ft_memcpy(future_player, &app->player, sizeof(t_player));
	ml_vector3_add(future_player->pos, new_add, future_player->pos);
	player_update_aabb(future_player);
}

/*
** Shoot 32 rays from top and bottom corners of a cylinder collider on player.
** Start half height below player position, and above.
*/

static void		cylinder_rays_from_aabb(t_player *future_player,
					t_ray rays[64])
{
	uint32_t	angle;
	int32_t		i;
	t_vec3		cylinder_start_down;
	t_vec3		cylinder_start_up;
	t_mat4		rotation_x;

	angle = 360 / 32;
	ml_vector3_copy((t_vec3){future_player->aabb.xyz_min[0],
		future_player->pos[1] + future_player->aabb.size[1] / 2.0,
		future_player->aabb.xyz_min[2]}, cylinder_start_down);
	ml_vector3_copy((t_vec3){future_player->aabb.xyz_min[0],
		future_player->pos[1] - future_player->aabb.size[1] / 2.0,
		future_player->aabb.xyz_min[2]}, cylinder_start_up);
	i = -1;
	while (++i < 32)
	{
		ml_matrix4_rotation_y(ml_rad(i * angle), rotation_x);
		// Localize cylinder start into ray origin
		ml_vector3_sub(cylinder_start_down, future_player->pos, rays[i].origin);
		// Rotate origin by angle
		ml_matrix4_mul_vec3(rotation_x, rays[i].origin, rays[i].origin);
		// Place back where origin should be
		ml_vector3_add(rays[i].origin, future_player->pos, rays[i].origin);
		// Get direction from player center at same y height to ray origin
		ml_vector3_sub(rays[i].origin, (t_vec3){future_player->pos[0],
			rays[i].origin[1], future_player->pos[2]},
			rays[i].dir);
		// Set ray
		l3d_ray_set(rays[i].dir, rays[i].origin, &rays[i]);
		// Same for cylinder start up
		ml_vector3_sub(cylinder_start_up, future_player->pos, rays[i + 32].origin);
		ml_matrix4_mul_vec3(rotation_x, rays[i + 32].origin, rays[i + 32].origin);
		ml_vector3_add(rays[i + 32].origin, future_player->pos, rays[i + 32].origin);
		ml_vector3_sub(rays[i + 32].origin, (t_vec3){future_player->pos[0],
			rays[i + 32].origin[1], future_player->pos[2]},
			rays[i + 32].dir);
		l3d_ray_set(rays[i + 32].dir, rays[i + 32].origin, &rays[i + 32]);
	}
}

/*
** Direct rays from collider
** See if they hit & subtract movement add so we limit the movement by the hit
** triangles.
*/

void			collision_limit_player_horizontal(t_doom3d *app, t_vec3 add)
{
	int32_t		i;
	t_player	future_player;
	t_hits		*hits;
	t_hit		*closest_triangle_hit;
	t_ray		rays[64];

	set_future_player(app, add, &future_player);
	cylinder_rays_from_aabb(&future_player, rays);
	i = -1;
	while (++i < 32)
	{
		l3d_ray_set(rays[i].dir, rays[i].origin, &rays[i]);
		hits = NULL;
		if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree,
								rays[i].origin, rays[i].dir, &hits))
		{
			closest_triangle_hit = NULL;
			l3d_get_closest_triangle_hit_at_range(hits, &closest_triangle_hit,
													-1, 0.1 * app->unit_size);
			if (closest_triangle_hit != NULL)
				limit_move_add_by_collision(closest_triangle_hit->normal, add);
			l3d_delete_hits(&hits);
		}
	}
}

/*
** Updates the sphere collider and casts rays.
*/

void			player_collider_update(t_doom3d *app)
{
	ml_vector3_copy(app->player.pos, app->player.collider.sphere.pos);
	ml_vector3_sub(app->player.collider.sphere.pos,
		(t_vec3){0.0, -0.5 * app->unit_size, 0.0},
		app->player.collider.sphere.pos);
	l3d_cast_rays_sphere(app->player.collider.rays,
		(uint32_t[2]){COLLIDER_RAY_COUNT, COLLIDER_RAY_COUNT},
			&app->player.collider.sphere);
	return ;
}

t_bool			is_player_grounded(t_doom3d *app)
{
	t_hits		*hits;
	t_ray		ray;
	int			i;
	t_hit		*closest_triangle_hit;

	i = -1;
	hits = NULL;
	while (++i < COLLIDER_RAY_TOTAL)
	{
		ray = app->player.collider.rays[i];
		if (ml_vector3_angle_deg(ray.dir, (t_vec3){0.0, 1.0, 0.0})
			< SLOPE_ANGLE_THRESHOLD
			&& l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, ray.origin,
				ray.dir, &hits))
		{
			closest_triangle_hit = NULL;
			l3d_get_closest_triangle_hit_at_range(hits, &closest_triangle_hit,
				-1, app->player.collider.sphere.radius);
			if (closest_triangle_hit != NULL)
			{
				l3d_delete_hits(&hits);
				return(true);
			}
		}
	}
	l3d_delete_hits(&hits);
	return (false);
}