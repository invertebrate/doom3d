/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 16:04:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		handle_wasd_input(t_doom3d *app)
{
	int32_t		amount;

	amount = 1;
	if (app->keyboard.state[SDL_SCANCODE_W])
		push_custom_event(app, event_player_move, (void*)move_forward,
			(void*)(intptr_t)amount);
	if (app->keyboard.state[SDL_SCANCODE_A])
		push_custom_event(app, event_player_move, (void*)move_strafe_left,
			(void*)(intptr_t)amount);
	if (app->keyboard.state[SDL_SCANCODE_S])
		push_custom_event(app, event_player_move, (void*)move_backward,
			(void*)(intptr_t)amount);
	if (app->keyboard.state[SDL_SCANCODE_D])
		push_custom_event(app, event_player_move, (void*)move_strafe_right,
			(void*)(intptr_t)amount);
}

static t_bool	wasd_not_pressed(t_doom3d *app)
{
	return (!(app->keyboard.state[SDL_SCANCODE_W]) &&
			!(app->keyboard.state[SDL_SCANCODE_A]) &&
			!(app->keyboard.state[SDL_SCANCODE_S]) &&
			!(app->keyboard.state[SDL_SCANCODE_D]));
}

static void		handle_weapon_equip_input(t_doom3d *app)
{
	if (app->keyboard.state[SDL_SCANCODE_4])
		push_custom_event(app, event_player_weapon_equip,
			(void*)weapon_rpg, NULL);
	else if (app->keyboard.state[SDL_SCANCODE_3])
		push_custom_event(app, event_player_weapon_equip,
			(void*)weapon_shotgun, NULL);
	else if (app->keyboard.state[SDL_SCANCODE_2])
		push_custom_event(app, event_player_weapon_equip,
			(void*)weapon_pistol, NULL);
	else if (app->keyboard.state[SDL_SCANCODE_1])
		push_custom_event(app, event_player_weapon_equip,
			(void*)weapon_fist, NULL);
}

static void		handle_game_keyboard_state(t_doom3d *app)
{
	if (app->player.physics_state == physics_state_grounded ||
		app->player.can_fly)
	{
		handle_wasd_input(app);
		if (wasd_not_pressed(app))
			app->player.is_moving = false;
		if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
			app->player.is_running = true;
		if (app->keyboard.state[SDL_SCANCODE_LCTRL] &&
			app->player.physics_state == physics_state_grounded)
			push_custom_event(app, event_player_crouch, (void*)true, NULL);
		if (app->player.is_crouching &&
			!app->keyboard.state[SDL_SCANCODE_LCTRL])
			push_custom_event(app, event_player_crouch, (void*)false, NULL);
		if (app->player.is_crouching ||
			(!app->keyboard.state[SDL_SCANCODE_LSHIFT] &&
				app->player.physics_state == physics_state_grounded))
			app->player.is_running = false;
	}
	if (app->keyboard.state[SDL_SCANCODE_R])
		push_custom_event(app, event_player_reload, NULL, NULL);
	if (app->keyboard.state[SDL_SCANCODE_E])
		push_custom_event(app, event_player_interact, NULL, NULL);
	handle_weapon_equip_input(app);
}

/*
** Keyboard state handling, both editor & game
*/

void			handle_keyboard_state_input(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		handle_game_keyboard_state(app);
	}
	else if (app->active_scene->scene_id == scene_id_editor3d &&
		!SDL_IsTextInputActive() && !app->editor.is_saving)
	{
		handle_editor_keyboard_state_input(app);
	}
}
