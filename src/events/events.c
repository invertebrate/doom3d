/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/03 00:16:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_bool			editor_popup_menu_open(t_doom3d *app)
{
	return (app->editor.editor_menu != NULL &&
			app->editor.editor_menu->is_open);
}

static void		editor_input_events_handle(t_doom3d *app, SDL_Event event)
{
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		handle_editor_saving(app, event);
		handle_editor_selection(app, event);
	}
	if (event.type == SDL_MOUSEWHEEL)
	{
		editor_vertical_move(app, -event.wheel.y * 30);
	}
}

static void		doom3d_button_events_handle(t_doom3d *app, SDL_Event event)
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
** Main API for event handling
** 1. Poll state and handle keyboard & mouse state (in-game actions mostly
** where there should not be any lag)
** 2. General input events, e.g. debug mode, set normal map shading, set
** full screen etc.
** 3. Game input events: menu options, pausing, etc.
*/

void			events_handle(t_doom3d *app)
{
	SDL_Event	event;

	SDL_PumpEvents();
	app->mouse.state = SDL_GetMouseState(&app->mouse.x, &app->mouse.y);
	app->keyboard.state = SDL_GetKeyboardState(NULL);
	if (!app->active_scene->is_paused)
	{
		mouse_state_handle(app);
		keyboard_state_handle(app);
	}
	while (SDL_PollEvent(&event))
	{
		general_input_events_handle(app, event);
		if (app->active_scene->scene_id == scene_id_editor3d &&
			!editor_popup_menu_open(app))
			editor_input_events_handle(app, event);
		doom3d_button_events_handle(app, event);
	}
}
