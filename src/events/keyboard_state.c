/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 02:08:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		handle_wasd_input(t_doom3d *app)
{
	t_vec3	dir;

	if (app->keyboard.state[SDL_SCANCODE_W])
	{
		get_move_dir(app, move_forward, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
	if (app->keyboard.state[SDL_SCANCODE_A])
	{
		get_move_dir(app, move_strafe_left, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
	if (app->keyboard.state[SDL_SCANCODE_S])
	{
		get_move_dir(app, move_backward, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
	if (app->keyboard.state[SDL_SCANCODE_D])
	{
		get_move_dir(app, move_strafe_right, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
}

static t_bool	wasd_not_pressed(t_doom3d *app)
{
	return (!(app->keyboard.state[SDL_SCANCODE_W]) &&
			!(app->keyboard.state[SDL_SCANCODE_A]) &&
			!(app->keyboard.state[SDL_SCANCODE_S]) &&
			!(app->keyboard.state[SDL_SCANCODE_D]));
}

static void		handle_weapon_equip(t_doom3d *app)
{
	if (app->keyboard.state[SDL_SCANCODE_4])
		weapon_equip(app, weapon_rpg);
	else if (app->keyboard.state[SDL_SCANCODE_3])
		weapon_equip(app, weapon_shotgun);
	else if (app->keyboard.state[SDL_SCANCODE_2])
		weapon_equip(app, weapon_glock);
	else if (app->keyboard.state[SDL_SCANCODE_1])
		weapon_equip(app, weapon_fist);
}

static void		handle_game_keyboard_state(t_doom3d *app)
{
	if (app->player.is_grounded || app->player.can_fly)
	{
		handle_wasd_input(app);
		if (wasd_not_pressed(app))
			app->player.is_moving = false;
		if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
			app->player.is_running = true;
		if (app->keyboard.state[SDL_SCANCODE_LCTRL] && app->player.is_grounded)
			player_crouch(app, true);
		if (!app->keyboard.state[SDL_SCANCODE_LCTRL])
			player_crouch(app, false);
		if (app->player.is_crouching ||
			(!app->keyboard.state[SDL_SCANCODE_LSHIFT] &&
				app->player.is_grounded))
			app->player.is_running = false;
		if (app->keyboard.state[SDL_SCANCODE_R])
			player_reload(app);
	}
	handle_weapon_equip(app);
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
