/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/01 17:08:52 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		keyboard_game_state_handle(t_doom3d *app)
{
	t_vec3	dir;

	if (app->player.is_grounded)
	{
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
		if (!(app->keyboard.state[SDL_SCANCODE_W]) &&
			!(app->keyboard.state[SDL_SCANCODE_A]) &&
			!(app->keyboard.state[SDL_SCANCODE_S]) &&
			!(app->keyboard.state[SDL_SCANCODE_D]))
			app->player.is_moving = false;
		if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
			app->player.is_running = true;
		else if (app->player.is_grounded)
			app->player.is_running = false;	
	}
	if (app->keyboard.state[SDL_SCANCODE_4])
		weapon_equip(app, weapon_rpg);
	else if (app->keyboard.state[SDL_SCANCODE_3])
		weapon_equip(app, weapon_shotgun);
	else if (app->keyboard.state[SDL_SCANCODE_2])
		weapon_equip(app, weapon_glock);
	else if (app->keyboard.state[SDL_SCANCODE_1])
		weapon_equip(app, weapon_fist);
	//if (app->keyboard.state[SDL_SCANCODE_F10])
	//	app->player.flying = (app->player.flying + 1) % 2;
	// if (app->keyboard.state[SDL_SCANCODE_E]) //Later for interaction
}

static void		handle_editor_transform(t_doom3d *app)
{
	static uint32_t		last_changed;
	uint32_t			diff;
	int					shift;

	shift = 1;
	if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
		shift = 10;
	diff = SDL_GetTicks() - last_changed;
	if (app->editor.is_saving || !app->editor.selected_object)
		return ;
	if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_UP])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0, 0, 0.1 * app->unit_size * shift);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_RIGHT])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0.1 * app->unit_size * shift, 0, 0);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_DOWN])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0, 0, -0.1 * app->unit_size * shift);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_LEFT])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			-0.1 * app->unit_size * shift, 0, 0);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_O])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0, -0.1 * app->unit_size * shift, 0);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_L])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0, 0.1 * app->unit_size * shift, 0);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 50 &&
		app->keyboard.state[SDL_SCANCODE_LEFTBRACKET])
	{
		l3d_3d_object_scale(app->editor.selected_object,
			1.0 / 1.1, 1.0 / 1.1, 1.0 / 1.1);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 50 &&
		app->keyboard.state[SDL_SCANCODE_RIGHTBRACKET])
	{
		l3d_3d_object_scale(app->editor.selected_object,
			1.1, 1.1, 1.1);
		after_editor_transform(app, &last_changed);
	}
	if (diff > 50 && app->keyboard.state[SDL_SCANCODE_KP_PLUS] &&
		app->editor.patrol_slot < MAX_PATROL_NODES)
	{
		app->editor.patrol_slot++;
		ft_printf("patrol slot = %d\n", app->editor.patrol_slot);
	}
	if (diff > 50 && app->keyboard.state[SDL_SCANCODE_KP_MINUS] &&
		app->editor.patrol_slot > 0)
	{
		app->editor.patrol_slot--;
		ft_printf("patrol slot = %d\n", app->editor.patrol_slot);
	}
}

static void		keyboard_editor_state_handle(t_doom3d *app)
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
	if (app->keyboard.state[SDL_SCANCODE_W] ||
		app->keyboard.state[SDL_SCANCODE_A] ||
		app->keyboard.state[SDL_SCANCODE_S] ||
		app->keyboard.state[SDL_SCANCODE_D])
		app->editor.is_moving = true;
	else
		app->editor.is_moving = false;
	handle_editor_transform(app);
}

void			keyboard_state_handle(t_doom3d *app)
{

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
