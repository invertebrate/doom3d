/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/10 19:30:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		main_game_input_events_handle(t_doom3d *app, SDL_Event event)
{
	if (app->active_scene->is_paused)
	{
		main_game_menu_event_handle(app, event);
	}
}

static void		game_input_events_handle(t_doom3d *app, SDL_Event event)
{
	if (app->active_scene->scene_id == scene_id_main_menu)
		main_menu_event_handle(app, event);
	else if (app->active_scene->scene_id == scene_id_main_menu_settings)
		main_menu_settings_event_handle(app, event);
	else if (app->active_scene->scene_id == scene_id_main_game)
		main_game_input_events_handle(app, event);
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

	if (!app->active_scene->is_paused)
	{
		SDL_PumpEvents();
		mouse_state_handle(app);
		keyboard_state_handle(app);
	}
	while (SDL_PollEvent(&event))
	{
		general_input_events_handle(app, event);
		game_input_events_handle(app, event);
	}
}
