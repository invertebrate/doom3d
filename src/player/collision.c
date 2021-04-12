/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/12 19:09:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** https://gamedev.stackexchange.com/questions/49956/
** collision-detection-smooth-wall-sliding-no-bounce-effect
*/

static void		limit_movement_add_by_collision(t_vec3 collision_normal,
					t_vec3 dir_add)
{
	t_vec3		direction_wall_part;

	ml_vector3_normalize(collision_normal, collision_normal);
	ml_vector3_mul(collision_normal,
		ml_vector3_dot(dir_add, collision_normal), direction_wall_part);
	if (direction_wall_part[1] > 0)
		direction_wall_part[1] = 0;
	ml_vector3_sub(dir_add, direction_wall_part, dir_add);
}

static void		set_future_player(t_doom3d *app, t_vec3 add,
					t_player *future_player)
{
	t_vec3	new_add;

	ml_vector3_add(add, 
			(t_vec3) {0, -app->player.player_height / 4, 0}, new_add);
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
	while (++i < 64)
	{
		l3d_ray_set(rays[i].dir, rays[i].origin, &rays[i]);
		hits = NULL;
		if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, rays[i].origin,
			rays[i].dir, &hits))
		{
			closest_triangle_hit = NULL;
			l3d_get_closest_triangle_hit_at_range(hits,
				&closest_triangle_hit, -1,
				0.1 * app->unit_size);
			if (closest_triangle_hit != NULL)
				limit_movement_add_by_collision(closest_triangle_hit->normal,
					add);
			l3d_delete_hits(&hits);
		}
	}
}
