/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 23:32:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_update_aabb(t_player *player)
{
	player->aabb.xyz_min[0] = player->pos[0] - player->aabb.size[0] / 2.0;
	player->aabb.xyz_min[1] = player->pos[1] - player->aabb.size[1] / 2.0;
	player->aabb.xyz_min[2] = player->pos[2] - player->aabb.size[2] / 2.0;
	player->aabb.xyz_max[0] = player->pos[0] + player->aabb.size[0] / 2.0;
	player->aabb.xyz_max[1] = player->pos[1] + player->aabb.size[1] / 2.0;
	player->aabb.xyz_max[2] = player->pos[2] + player->aabb.size[2] / 2.0;
	ml_vector3_copy(player->pos, player->aabb.center);
}

void	update_player_physics_state(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		app->player.physics_state = physics_state_not_applied;
		return ;
	}
	if (is_player_grounded(app))
	{
		if (app->player.velocity[1] >= 0)
			app->player.physics_state = physics_state_grounded;
		else
			app->player.physics_state = physics_state_not_grounded;
	}
	else
	{
		app->player.physics_state = physics_state_not_grounded;
	}
}

static void	player_update_camera_pos(t_doom3d *app)
{
	ml_matrix4_translation(app->player.pos[0],
		app->player.pos[1], app->player.pos[2], app->player.translation);
	ml_matrix4_inverse(app->player.translation, app->player.inv_translation);
	update_player_camera(app);
	update_third_person_camera(app);
}

void	update_player(t_doom3d *app)
{
	if ((app->active_scene->scene_id != scene_id_main_game
			&& !app->active_scene->is_paused)
		&& app->active_scene->scene_id != scene_id_editor3d)
		return ;
	player_move(app);
	player_colliders_update(app);
	update_player_physics_state(app);
	forces_update_player(app);
	player_update_aabb(&app->player);
	player_animation_update(app);
	player_update_camera_pos(app);
	player_flashlight_update(app);
}
