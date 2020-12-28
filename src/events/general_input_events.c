/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_input_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:40:54 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/28 19:36:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		set_objects_shading_opts(t_doom3d *app, t_shading_opts opts)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		l3d_object_set_shading_opts(app->active_scene->objects[i], opts);
}

static void		handle_main_game_general_keyup_events(t_doom3d *app,
					SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_n)
	{
		app->is_normal_map = !app->is_normal_map;
		if (app->is_normal_map)
			set_objects_shading_opts(app,
				app->active_scene->objects[0]->material->shading_opts |
				e_shading_normal_map);
		else
			set_objects_shading_opts(app,
				app->active_scene->objects[0]->material->shading_opts ^
				e_shading_normal_map);
	}
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

static void		handle_general_keyup_events(t_doom3d *app, SDL_Event event)
{
	if (app->active_scene->scene_id == scene_id_main_game)
		handle_main_game_general_keyup_events(app, event);
	if (event.key.keysym.sym == SDLK_g)
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
** Handle events that aren't related to menus or game, like exiting or esc
** or setting to full screen, or disabling debug info
*/

void			general_input_events_handle(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_QUIT)
	{
		app->is_running = false;
	}
	if (!SDL_IsTextInputActive() && !app->editor.is_saving)
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			app->is_running = false;
		if (event.type == SDL_KEYUP)
			handle_general_keyup_events(app, event);
	}
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		handle_editor_saving(app, event);
		handle_editor_selection(app, event);
	}
}
