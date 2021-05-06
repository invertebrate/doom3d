/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/06 20:00:50 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			player_update_aabb(t_player *player)
{
	player->aabb.xyz_min[0] = player->pos[0] - player->aabb.size[0] / 2.0;
	player->aabb.xyz_min[1] = player->pos[1] - player->aabb.size[1] / 2.0;
	player->aabb.xyz_min[2] = player->pos[2] - player->aabb.size[2] / 2.0;
	player->aabb.xyz_max[0] = player->pos[0] + player->aabb.size[0] / 2.0;
	player->aabb.xyz_max[1] = player->pos[1] + player->aabb.size[1] / 2.0;
	player->aabb.xyz_max[2] = player->pos[2] + player->aabb.size[2] / 2.0;
	ml_vector3_copy(player->pos, player->aabb.center);
}

void			player_nudge_grounded(t_doom3d *app)
{
	t_hits		*hits;
	t_ray		ray;
	int			i;
	t_hit		*closest_triangle_hit;
	int			max_index;
	float		max_mag;
	t_vec3		nudge_vector;
	t_vec3		max_vector;

	i = -1;
	max_index = 0;
	max_mag = 0.0;
	ft_memset(max_vector, 0, sizeof(max_vector));
	ft_memset(nudge_vector, 0, sizeof(nudge_vector));
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
				ml_vector3_mul(ray.dir, app->player.collider.sphere.radius, nudge_vector);
				ml_vector3_add(nudge_vector, app->player.collider.sphere.pos, nudge_vector);
				ml_vector3_sub(nudge_vector, closest_triangle_hit->hit_point, nudge_vector);
				if (ml_vector3_mag(nudge_vector) > max_mag)
				{
					ml_vector3_copy(nudge_vector, max_vector);
					max_index = i;
				}

				l3d_delete_hits(&hits);
				return(true);
			}
		}
	}
	l3d_delete_hits(&hits);
	return (false);
}

void			update_player_physics_state(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		app->player.physics_state = physics_state_not_applied;
		return ;
	}
	if (is_player_grounded(app))
	{
		app->player.physics_state = physics_state_grounded;
		player_nudge_grounded(app);
	}
	else
	{
		app->player.physics_state = physics_state_not_grounded;
	}
}

void			update_player(t_doom3d *app)
{
	static uint64_t	dt_sum;

	dt_sum = dt_sum > 0 ? dt_sum : 0;
	if ((app->active_scene->scene_id == scene_id_main_game &&
		!app->active_scene->is_paused) ||
			app->active_scene->scene_id == scene_id_editor3d)
		player_move(app);
	else
		return ;
	player_collider_update(app);
	update_player_physics_state(app);
	if (dt_sum > FORCES_UPDATE_MS)
	{
		forces_update_player(app);
		dt_sum = 0;
	}
	dt_sum += app->info.delta_time;
	player_update_aabb(&app->player);
	player_animation_update(app);
	player_flashlight_update(app);
	if (is_player_grounded(app))
		ft_printf("GROUNDED\n");
	else
		ft_printf("NOT GROUNDED\n");
}
