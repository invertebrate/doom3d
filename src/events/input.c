/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 18:50:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** This function is responsible for passing event info to buttons and button
** groups (menus) so their on clicks are handled.
*/

static void	handle_all_button_events(t_doom3d *app, SDL_Event event)
{
	int32_t	i;

	if (editor_popup_menu_open(app))
	{
		button_popup_menu_events_handle(app->editor.editor_menu,
			app->mouse, event);
		return ;
	}
	if (app->active_scene->scene_id == scene_id_editor3d
		&& (app->editor.is_moving || app->editor.is_rotating))
		return ;
	if ((app->active_scene->scene_id != scene_id_main_game)
		|| (app->active_scene->scene_id == scene_id_main_game
			&& app->active_scene->is_paused))
	{
		i = -1;
		while (++i < (int32_t)app->active_scene->num_button_menus)
			button_group_events_handle(app->active_scene->menus[i],
				app->mouse, event);
	}
}

static void	handle_wheel(t_doom3d *app, SDL_Event event)
{
	int32_t	weapon;
	int32_t	add;

	add = -1;
	if (event.wheel.y > 0)
		add = 1;
	if (!app->settings.is_third_person)
	{
		weapon = app->player.equipped_weapon->id + add;
		if (weapon < 0)
			weapon = 3;
		if (weapon >= 4)
			weapon = 0;
		push_custom_event(app, event_player_weapon_equip,
			(void *)(intptr_t)weapon, NULL);
	}
	else
		push_custom_event(app, event_third_person_zoom,
			(void *)(intptr_t)(add * -1), NULL);
}

/*
** Handle button events for game including weapon switch via mouse wheel
** See keyboard_state.c and mouse_state.c for movement
*/

void	handle_game_input_events(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		push_custom_event(app, event_player_jump, NULL, NULL);
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_9)
		push_custom_event(app, event_player_toggle_flight, NULL, NULL);
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_0)
		push_custom_event(app, event_player_toggle_collision, NULL, NULL);
	if (event.type == SDL_MOUSEWHEEL)
		handle_wheel(app, event);
}

/*
** Handle control flow events (exit etc. pausing)
** Handle game input events if inside game
** Handle editor input events if inside editor
** Tie buttons to receive events
*/

void	handle_input_events(t_doom3d *app, SDL_Event event)
{
	if (app->settings.is_debug)
	{
		if (event.type == SDL_KEYDOWN)
			LOG_DEBUG("Key %s pressed", SDL_GetKeyName(event.key.keysym.sym));
		if (event.type == SDL_KEYUP)
			LOG_DEBUG("Key %s released", SDL_GetKeyName(event.key.keysym.sym));
		if (event.type == SDL_MOUSEBUTTONDOWN)
			LOG_DEBUG("Mouse %d pressed", event.button.button);
		if (event.type == SDL_MOUSEBUTTONUP)
			LOG_DEBUG("Mouse %d released", event.button.button);
		if (event.type == SDL_MOUSEWHEEL)
			LOG_DEBUG("Mouse wheel scrolled %d", event.wheel.y);
	}
	handle_control_flow_events(app, event);
	if (app->active_scene->scene_id == scene_id_main_game
		&& !app->active_scene->is_paused)
		handle_game_input_events(app, event);
	if (app->active_scene->scene_id == scene_id_editor3d)
		handle_editor_input_events(app, event);
}

/*
** Root of all event handling
** 1. Update event queue by pumping events
** 2. Update mouse and key state (correct mouse pos for fullscreen)
** 3. Handle mouse & key state dependent actions
** 4. Handle custom events
** 5. Handle input events (for game, for editor, and for button clicks)
*/

void	handle_events(t_doom3d *app)
{
	SDL_Event			event;

	SDL_PumpEvents();
	app->mouse.state = SDL_GetMouseState(&app->mouse.x, &app->mouse.y);
	if (app->window->is_fullscreen)
		correct_fullscreen_mouse_pos(app);
	app->keyboard.state = SDL_GetKeyboardState(NULL);
	if (!app->active_scene->is_paused)
	{
		handle_mouse_state_input(app);
		handle_keyboard_state_input(app);
	}
	while (SDL_PollEvent(&event))
	{
		if (event.type == app->custom_event_type)
			handle_custom_events(app, event);
		else
		{
			handle_input_events(app, event);
			handle_all_button_events(app, event);
		}
	}
}
