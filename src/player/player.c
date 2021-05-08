/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/08 17:55:49 by veilo            ###   ########.fr       */
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
	float		max_mag;
	t_vec3		nudge_vector;
	t_vec3		max_vector;
	t_vec3		hitvec;
	float		current_mag;

	i = -1;
	max_mag = 0.0;
	ft_memset(max_vector, 0, sizeof(max_vector));
	ft_memset(hitvec, 0, sizeof(hitvec));
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
				t_vec3	tdir;
				ml_vector3_mul(ray.dir, closest_triangle_hit->t, tdir);
				// ft_printf("t magnitude: %f\n", closest_triangle_hit->t);
				ml_vector3_sub(tdir, nudge_vector, nudge_vector);
				// ft_printf("nudge: \n");
				// ml_vector3_print(nudge_vector);
				current_mag = ml_vector3_mag(nudge_vector);
				if (current_mag > max_mag)
				{
					// ml_vector3_sub(closest_triangle_hit->hit_point, ray.origin, hitvec);
					ml_vector3_copy(nudge_vector, max_vector);//nudge vector calculation might be off
					max_mag = current_mag;
				}
				// return(true);
			}
		}
	}
	ml_vector3_copy(max_vector, app->player.nudge);//test
	ml_vector3_add(app->player.pos, max_vector, app->player.pos);
	l3d_delete_hits(&hits);
	// return (false);
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
	}
	else
	{
		app->player.physics_state = physics_state_not_grounded;
	}
}

static void		player_update_camera_pos(t_doom3d *app)
{
	ml_matrix4_translation(app->player.pos[0],
	app->player.pos[1], app->player.pos[2], app->player.translation);
	ml_matrix4_inverse(app->player.translation, app->player.inv_translation);
	update_player_camera(app);
	update_third_person_camera(app);
}

void			player_snap_to_ground(t_doom3d *app)
{
	LOG_INFO("Player snapped to ground\n");
	(void)app;
}

void			player_collision_handle_ground_snap(t_doom3d *app,
					t_physics_state *prev_state)
{
	if (*prev_state == physics_state_grounded
		&& app->player.physics_state == physics_state_not_grounded)
		{
			if (fabs(app->player.velocity[1]) > L3D_EPSILON )
			{
				player_snap_to_ground(app);
				ft_printf("Player snapped to ground\n");
				app->player.physics_state = physics_state_grounded;
				return ;
			}
			else
			{
				ft_printf("velocity was 0\n");
				*prev_state = physics_state_not_grounded;
			}
		}
	else if (app->player.physics_state == physics_state_not_grounded)
	{
		ft_printf("prev state was not grounded or current was grounded\n");
		*prev_state = physics_state_not_grounded;
	}
	(void)app;
	(void)prev_state;
}

void			update_player(t_doom3d *app)
{
	static t_physics_state	previous_frame_grounded = 1000;

	if ((app->active_scene->scene_id != scene_id_main_game &&
		!app->active_scene->is_paused) &&
			app->active_scene->scene_id != scene_id_editor3d)
		return ;

	if (app->active_scene->scene_id != scene_id_editor3d)
	{
		update_player_physics_state(app);
		player_collision_handle_ground_snap(app, &previous_frame_grounded);
	}
	if (app->player.physics_state == physics_state_grounded)
	{
		previous_frame_grounded = physics_state_grounded;
		ft_printf("GROUNDED\n");
		player_nudge_grounded(app);

	}
	else
	{
		previous_frame_grounded = physics_state_not_grounded;
		ft_printf("NOT GROUNDED\n");
	}

	forces_update_player(app);

	player_move(app);

	player_collider_update(app);
	player_update_aabb(&app->player);
	player_animation_update(app);
	player_flashlight_update(app);
	player_update_camera_pos(app);
	ft_printf("frame=+++++++++++++++++++\n");
}


