/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/09 16:29:15 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** https://gamedev.stackexchange.com/questions/49956/
** collision-detection-smooth-wall-sliding-no-bounce-effect
*/

static void		limit_move_add_by_collision(t_vec3 collision_normal,
					t_vec3 dir_add)
{
	t_vec3		direction_collider_part;
	float		dot;

	ml_vector3_normalize(collision_normal, collision_normal);
	dot = ml_vector3_dot(dir_add, collision_normal);
	if (dot < 0)
	{
		ml_vector3_mul(collision_normal, dot, direction_collider_part);
		ml_vector3_sub(dir_add, direction_collider_part, dir_add);
	}
	//When multiple triangles are hit, check ray from player directly along y axis
	//and choose the triangle that it hits to be the one determining the movement
	//ground needs to be changed so that it is planes and not boxes
}

 void		limit_move_add_by_slope(t_vec3 slope_normal,
					t_vec3 dir_add)
{
	t_vec3		add_along_normal;
	float		dot;

	ml_vector3_normalize(slope_normal, slope_normal);
	dot = ml_vector3_dot(dir_add, slope_normal);
	if (dot > 0)
	{
		ml_vector3_mul(slope_normal, dot, add_along_normal);
		ml_vector3_sub(dir_add, add_along_normal, dir_add);
	}

}

/*
** Direct rays from collider
** See if they hit & subtract movement add so we limit the movement by the hit
** triangles.
*/

void	player_limit_move_by_collision(t_doom3d *app, t_vec3 add)
{
	int32_t		i;
	t_hits		*hits;
	t_hit		*closest_triangle_hit;

	i = -1;
	while (++i < COLLIDER_RAY_TOTAL)
	{
		hits = NULL;
		if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree,
			app->player.collider.rays[i].origin, app->player.collider.rays[i].dir, &hits))
		{
			closest_triangle_hit = NULL;
			l3d_get_closest_triangle_hit_at_range(hits, &closest_triangle_hit,
				-1, app->player.collider.sphere.radius);
			if (closest_triangle_hit != NULL)
			{
				limit_move_add_by_collision(closest_triangle_hit->normal, add);
				if (fabs(ml_vector3_angle_deg(closest_triangle_hit->normal,
						(t_vec3){0.0, 1.0, 0.0}) - 180) < SLOPE_ANGLE_THRESHOLD
					&& app->player.physics_state != physics_state_jumping)
					limit_move_add_by_slope(closest_triangle_hit->normal, add);

			}
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
