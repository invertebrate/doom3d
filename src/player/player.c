/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/30 14:08:02 by ahakanen         ###   ########.fr       */
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

static void		nudge_player_to_ground(t_doom3d *app)
{
	int	i;

	i = -1;
	while (!player_is_grounded(app) && ++i < app->player.aabb.size[1] / 20)
	{
		app->player.pos[1] += 10;
		player_update_aabb(&app->player);
	}
	if (player_is_grounded(app))
	{
		app->player.pos[1] -= 10;
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
	{
		app->player.physics_state = physics_state_jumping;
		if (player_hits_ceiling(app))
		{
			nudge_player_off_ceiling(app);
			app->player.velocity[1] = 0;
		}
	}
	else
	{
		is_grounded = player_is_grounded(app);
		if (!is_grounded)
		{
			if (should_nudge_to_ground(app))
				nudge_player_to_ground(app);
			else
				app->player.physics_state = physics_state_falling;
		}
		else if (is_grounded)
		{
			app->player.physics_state = physics_state_grounded;
			nudge_player_up(app);
			if (app->player.physics_state != prev_state)
				push_custom_event(app, event_effect_play,
				(void*)sf_landing, s_ini(0, 1, st_game, 1.0));
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
		LOG_DEBUG("Player physics state %s", physics_state);
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
	update_player_physics_state(app);
	if (dt_sum > FORCES_UPDATE_MS)
	{
		forces_update_player(app);
		dt_sum = 0;
	}
	dt_sum += app->info.delta_time;
	player_update_aabb(&app->player);
	player_animation_update(app);
	player_flashlight_update(&(app->player));
}
