/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/07 00:21:50 by ohakola          ###   ########.fr       */
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

void			player_init(t_doom3d *app, t_vec3 pos)
{
	ft_memset(&app->player, 0, sizeof(t_player));
	ft_memcpy(app->player.pos, pos, sizeof(t_vec3));
	ft_memcpy(app->player.forward, &(t_vec3){0, 0, Z_DIR}, sizeof(t_vec3));
	ft_memcpy(app->player.up, &(t_vec3){0, Y_DIR, 0}, sizeof(t_vec3));
	ft_memcpy(app->player.sideways, &(t_vec3){X_DIR, 0, 0}, sizeof(t_vec3));
	if (app->active_scene->scene_id == scene_id_editor3d)
		app->player.speed = PLAYER_SPEED * 2;
	else
		app->player.speed = PLAYER_SPEED;
	app->player.rot_speed = PLAYER_ROTATION_SPEED;
	app->player.rot_x = 0;
	app->player.rot_y = 0;
	app->player.player_height = PLAYER_HEIGHT * app->unit_size;
	app->player.fire_rate_per_sec = 4.0;
	app->player.aabb.size[0] = app->unit_size / 2.0;
	app->player.aabb.size[1] = app->player.player_height;
	app->player.aabb.size[2] = app->unit_size / 2.0;
	app->player.hp = 100;
	app->player.physics_state = physics_state_grounded;
	app->player.jump_force = PLAYER_JUMP_FORCE;
	app->player.can_fly = false;
	ml_vector3_set(app->player.velocity, 0, 0, 0);
	ml_matrix4_id(app->player.rotation);
	ml_matrix4_id(app->player.inv_rotation);
	ml_matrix4_id(app->player.translation);
	ml_matrix4_id(app->player.inv_translation);
	player_move(app);
	player_update_aabb(&app->player);
	SDL_GetRelativeMouseState(NULL, NULL);
}

static void		nudge_player_up(t_doom3d *app)
{
	while (player_is_grounded(app))
	{
		app->player.pos[1] -= 10;
		player_update_aabb(&app->player);
	}
	if (!player_is_grounded(app))
	{
		app->player.pos[1] += 10;
		player_update_aabb(&app->player);
	}
}

void			update_player_physics_state(t_doom3d *app)
{
	t_physics_state	prev_state;
	const char		*physics_state;
	t_bool			is_grounded;

	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		app->player.physics_state = physics_state_not_applied;
		return ;
	}
	prev_state = app->player.physics_state;
	if (app->player.velocity[1] < 0)
		app->player.physics_state = physics_state_jumping;
	else
	{
		is_grounded = player_is_grounded(app);
		if (!is_grounded)
			app->player.physics_state = physics_state_falling;
		else if (is_grounded)
		{
			app->player.physics_state = physics_state_grounded;
			nudge_player_up(app);
		}
	}
	if (app->player.physics_state != prev_state)
	{
		physics_state = "UNKNOWN";
		if (app->player.physics_state == physics_state_jumping)
			physics_state = "JUMPING(or flying if can fly)";
		else if (app->player.physics_state == physics_state_falling)
			physics_state = "FALLING";
		else if (app->player.physics_state == physics_state_grounded)
			physics_state = "GROUNDED";
		LOG_INFO("Player physics state %s", physics_state);
	}
}

void			update_player(t_doom3d *app)
{
	if ((app->active_scene->scene_id == scene_id_main_game &&
		!app->active_scene->is_paused) ||
			app->active_scene->scene_id == scene_id_editor3d)
		player_move(app);
	else
		return ;
	update_player_physics_state(app);
	forces_update_player(app);
	player_update_aabb(&app->player);
	player_animation_update(app);
}