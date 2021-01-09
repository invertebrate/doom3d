/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/09 15:14:36 by ahakanen         ###   ########.fr       */
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
	if (app->keyboard.state[SDL_SCANCODE_3])
		inventory_equip(app, item_type_weapon);
	else if (app->keyboard.state[SDL_SCANCODE_2])
		inventory_equip(app, item_type_sidearm);
	else if (app->keyboard.state[SDL_SCANCODE_1])
		inventory_equip(app, item_type_melee);
	if (app->keyboard.state[SDL_SCANCODE_G])
		inventory_throw_weapon(app);
	if (app->keyboard.state[SDL_SCANCODE_F]) //test
	{
		printf("Picked up RPG!\n");//test
		inventory_pickup_weapon(app, (t_item) {item_rpg, item_type_weapon, 10, fire_projectile, 0.25}); //test
	}
}

static void		handle_editor_transform(t_doom3d *app)
{
	static uint32_t		last_changed;
	uint32_t			diff;

	diff = SDL_GetTicks() - last_changed;
	if (app->editor.is_saving || !app->editor.selected_object)
		return ;
	if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_UP])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0, 0, 0.1 * app->unit_size);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_RIGHT])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0.1 * app->unit_size, 0, 0);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_DOWN])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0, 0, -0.1 * app->unit_size);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_LEFT])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			-0.1 * app->unit_size, 0, 0);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_O])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0, -0.1 * app->unit_size, 0);
		after_editor_transform(app, &last_changed);
	}
	else if (diff > 20 &&
		app->keyboard.state[SDL_SCANCODE_L])
	{
		l3d_3d_object_translate(app->editor.selected_object,
			0, 0.1 * app->unit_size, 0);
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
	if (app->keyboard.state[SDL_SCANCODE_W] ||
		app->keyboard.state[SDL_SCANCODE_A] ||
		app->keyboard.state[SDL_SCANCODE_S] ||
		app->keyboard.state[SDL_SCANCODE_D])
		app->editor.is_moving = true;
	else
	{
		app->editor.is_moving = false;
	}
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
