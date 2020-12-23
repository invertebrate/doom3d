/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/23 13:50:10 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		editor_input_events_handle(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_MOUSEWHEEL)
	{
		player_scroll_editor(app, -event.wheel.y * 30);
	}
}

static void		game_input_events_handle(t_doom3d *app, SDL_Event event)
{
	int32_t	i;

	if (app->active_scene->scene_id == scene_id_editor3d)
		editor_input_events_handle(app, event);
	if ((!app->is_loading &&
			app->active_scene->scene_id != scene_id_main_game) ||
			(app->active_scene->scene_id == scene_id_main_game &&
				app->active_scene->is_paused))
	{
		app->mouse.state = SDL_GetMouseState(&app->mouse.x, &app->mouse.y);
		i = -1;
		while (++i < (int32_t)app->active_scene->num_menus)
		{
			if (!app->is_loading)
				button_group_events_handle(app->active_scene->menus[i],
					app->mouse, event);
		}
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
