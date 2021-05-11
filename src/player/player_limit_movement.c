/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_limit_movement.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:19:42 by veilo             #+#    #+#             */
/*   Updated: 2021/05/11 19:52:44 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** https://gamedev.stackexchange.com/questions/49956/
** collision-detection-smooth-wall-sliding-no-bounce-effect
*/

void	limit_move_add_by_collision(t_vec3 collision_normal,
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
}

void	limit_move_add_by_slope(t_vec3 slope_normal, t_vec3 dir_add)
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
** Rays from sphere collider
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
				app->player.collider.rays[i].origin,
				app->player.collider.rays[i].dir, &hits))
		{
			closest_triangle_hit = NULL;
			l3d_get_closest_triangle_hit_at_range(hits, &closest_triangle_hit,
				-1, app->player.collider.sphere.radius);
			if (closest_triangle_hit != NULL
				&& closest_triangle_hit->triangle->parent->type
				!= object_type_trigger)
				limit_move_add_by_collision(closest_triangle_hit->normal, add);
			l3d_delete_hits(&hits);
		}
	}
}

static void	player_handle_closest_hit_slope(t_doom3d *app,
	t_hit *closest_triangle_hit, t_vec3 add)
{
	if (closest_triangle_hit != NULL
		&& closest_triangle_hit->triangle->parent->type
		!= object_type_trigger)
	{
		if (fabs(ml_vector3_angle_deg(closest_triangle_hit->normal,
					(t_vec3){0.0, 1.0, 0.0}) - 180) < SLOPE_ANGLE_THRESHOLD
				&& app->player.physics_state == physics_state_grounded)
			limit_move_add_by_slope(closest_triangle_hit->normal, add);
		if (closest_triangle_hit->triangle->parent->type == object_type_npc
			&& ((t_npc*)closest_triangle_hit->triangle->parent->params)->type
			== npc_type_elevator)
		{
			app->player.pos[1] = closest_triangle_hit->hit_point[1]
				- app->player.collider_ground.cylinder.height * 1.2;
		}
	}
}

/*
** Rays from cylinder collider
** See if they hit & subtract movement add so we limit the movement by the hit
** triangles.
*/

void	player_limit_move_by_slope(t_doom3d *app, t_vec3 add)
{
	int32_t		i;
	t_hits		*hits;
	t_hit		*closest_triangle_hit;

	i = -1;
	while (++i < COLLIDER_RAY_TOTAL)
	{
		hits = NULL;
		if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree,
				app->player.collider_ground.rays[i].origin,
				app->player.collider_ground.rays[i].dir, &hits))
		{
			closest_triangle_hit = NULL;
			l3d_get_closest_triangle_hit_at_range(hits, &closest_triangle_hit,
				-1, app->player.collider_ground.cylinder.height);
			player_handle_closest_hit_slope(app, closest_triangle_hit, add);
			l3d_delete_hits(&hits);
		}
	}
}
