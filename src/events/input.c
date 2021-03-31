/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 02:39:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** This function is responsible for passing event info to buttons and button
** groups (menus) so their on clicks are handled.
*/

static void		handle_menu_button_events(t_doom3d *app, SDL_Event event)
{
	int32_t	i;

	if (editor_popup_menu_open(app))
	{
		button_popup_menu_events_handle(app->editor.editor_menu,
			app->mouse, event);
		return ;
	}
	if ((app->active_scene->scene_id != scene_id_main_game) ||
			(app->active_scene->scene_id == scene_id_main_game &&
				app->active_scene->is_paused))
	{
		if (app->active_scene->scene_id == scene_id_editor3d &&
			app->editor.is_moving)
			return ;
		i = -1;
		while (++i < (int32_t)app->active_scene->num_button_menus)
			button_group_events_handle(app->active_scene->menus[i],
				app->mouse, event);
	}
}

/*
** Handle button events for game including weapon switch via mouse wheel
*/

void			handle_game_input_events(t_doom3d *app, SDL_Event event)
{
	int32_t	weapon;
	int32_t	add;

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		player_jump(app);
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_9)
		app->player.can_fly = !app->player.can_fly;
	if (event.type == SDL_MOUSEWHEEL)
	{
		add = event.wheel.y > 0 ? 1 : -1;
		weapon = app->player.equipped_weapon->id + add;
		if (weapon < 0)
			weapon = 3;
		if (weapon >= 4)
			weapon = 0;
		weapon_equip(app, weapon);
	}
}

/*
** Handle control flow events (exit etc. pausing)
** Handle game input events if inside game
** Handle editor input events if inside editor
** Tie buttons to receive events
*/

void			handle_input_events(t_doom3d *app, SDL_Event event)
{
	handle_control_flow_events(app, event);
	if (app->active_scene->scene_id == scene_id_main_game &&
		!app->active_scene->is_paused)
		handle_game_input_events(app, event);
	if (app->active_scene->scene_id == scene_id_editor3d)
		handle_editor_input_events(app, event);
	handle_menu_button_events(app, event);
}

/*
** Root of all event handling
** 1. Update event queue by pumping events
** 2. Update mouse and key state
** 3. Handle mouse & key state dependent actions
** 4. Handle custom events
** 5. Handle input events (for game, for editor, and for button clicks)
*/

void			handle_events(t_doom3d *app)
{
	SDL_Event	event;

	SDL_PumpEvents();
	app->mouse.state = SDL_GetMouseState(&app->mouse.x, &app->mouse.y);
	app->keyboard.state = SDL_GetKeyboardState(NULL);
	if (!app->active_scene->is_paused)
	{
		handle_mouse_state(app);
		handle_keyboard_state(app);
	}
	while (SDL_PollEvent(&event))
	{
		if (event.type == app->custom_event_type)
			custom_events_handle(app, event);
		else
			handle_input_events(app, event);
	}
}
