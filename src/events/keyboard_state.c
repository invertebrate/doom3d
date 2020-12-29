/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/28 16:01:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		keyboard_game_state_handle(t_doom3d *app)
{
	float	speed;

	speed = (app->player.is_running ? app->player.speed * 1.5 :
		app->player.speed) * app->info.delta_time;
	if (app->keyboard.state[SDL_SCANCODE_W])
		player_move(app, move_forward, speed);
	if (app->keyboard.state[SDL_SCANCODE_A])
		player_move(app, move_strafe_left, speed);
	if (app->keyboard.state[SDL_SCANCODE_S])
		player_move(app, move_backward, speed);
	if (app->keyboard.state[SDL_SCANCODE_D])
		player_move(app, move_strafe_right, speed);
	if (!(app->keyboard.state[SDL_SCANCODE_W]) &&
		!(app->keyboard.state[SDL_SCANCODE_A]) &&
		!(app->keyboard.state[SDL_SCANCODE_S]) &&
		!(app->keyboard.state[SDL_SCANCODE_D]))
		app->player.is_moving = false;
	if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
		app->player.is_running = true;
	else
		app->player.is_running = false;
}

static void		keyboard_editor_state_handle(t_doom3d *app)
{
	float	speed;

	speed = app->player.speed * 20;
	if (app->keyboard.state[SDL_SCANCODE_W])
		player_move(app, move_forward, speed);
	if (app->keyboard.state[SDL_SCANCODE_A])
		player_move(app, move_strafe_left, speed);
	if (app->keyboard.state[SDL_SCANCODE_S])
		player_move(app, move_backward, speed);
	if (app->keyboard.state[SDL_SCANCODE_D])
		player_move(app, move_strafe_right, speed);
}

void			keyboard_state_handle(t_doom3d *app)
{

	app->keyboard.state = SDL_GetKeyboardState(NULL);
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		keyboard_game_state_handle(app);
	}
	else if (app->active_scene->scene_id == scene_id_editor3d &&
		!SDL_IsTextInputActive() && !app->editor.is_saving)
	{
		keyboard_editor_state_handle(app);
	}
}
