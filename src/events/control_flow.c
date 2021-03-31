/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:40:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 23:35:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		set_objects_shading_opts(t_doom3d *app, t_shading_opts opts)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
		if (app->active_scene->objects[i])
			l3d_object_set_shading_opts(app->active_scene->objects[i], opts);
}

/*
** Handle normal map settings toggle inside main game
*/

static void		handle_normal_map_settings_toggle(t_doom3d *app,
					SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_n)
	{
		app->settings.is_normal_map = !app->settings.is_normal_map;
		if (app->settings.is_normal_map)
			set_objects_shading_opts(app,
				app->active_scene->objects[0]->material->shading_opts |
				e_shading_normal_map);
		else
			set_objects_shading_opts(app,
				app->active_scene->objects[0]->material->shading_opts ^
				e_shading_normal_map);
	}
}

/*
** Handle pausing inside main game
*/

static void		handle_main_game_pause(t_doom3d *app, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_p &&
		app->active_scene->scene_id == scene_id_main_game)
	{
		app->active_scene->is_paused = !app->active_scene->is_paused;
		if (app->active_scene->is_paused)
		{
			SDL_ShowCursor(SDL_ENABLE);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else
		{
			SDL_ShowCursor(SDL_DISABLE);
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_GetRelativeMouseState(NULL, NULL);
		}
	}
}

/*
** Handle game pausing & normal map settings toggle inside main game
*/

static void		handle_debug_and_fullscreen_toggles(t_doom3d *app,
					SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_u)
		app->is_debug = !app->is_debug;
	if (event.key.keysym.sym == SDLK_f)
	{
		app->window->is_fullscreen = !app->window->is_fullscreen;
		if (app->window->is_fullscreen)
			SDL_SetWindowFullscreen(app->window->window, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(app->window->window, 0);
	}
}

/*
** Handle events that aren't related to menu clicks or game interaction,
** like exiting or esc or setting to full screen, or disabling debug info
*/

void			handle_control_flow_events(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_QUIT)
	{
		push_custom_event(app, event_quit, NULL, NULL);
	}
	if (!SDL_IsTextInputActive() && !app->editor.is_saving)
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			push_custom_event(app, event_quit, NULL, NULL);
		if (event.type == SDL_KEYUP)
		{
			if (app->active_scene->scene_id == scene_id_main_game)
			{
				handle_normal_map_settings_toggle(app, event);
				handle_main_game_pause(app, event);
			}
			handle_debug_and_fullscreen_toggles(app, event);
		}
	}
}
