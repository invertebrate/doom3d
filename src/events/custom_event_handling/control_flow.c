/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 00:07:48 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/11 22:36:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_quit(t_doom3d *app)
{
	app->is_running = false;
}

void	handle_toggle_pause_game(t_doom3d *app)
{
	app->active_scene->is_paused = !app->active_scene->is_paused;
	if (app->active_scene->is_paused)
	{
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		mp_typec(app, 0, 2, SPAUSED);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_GetRelativeMouseState(NULL, NULL);
		SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
		mp_typec(app, 0, 2, SPLAYING);
	}
}

void	handle_toggle_fullscreen(t_doom3d *app)
{
	app->window->is_fullscreen = !app->window->is_fullscreen;
	if (app->window->is_fullscreen)
	{
		SDL_SetWindowFullscreen(app->window->window,
			SDL_WINDOW_FULLSCREEN);
		window_resize(app->window, app->settings.width, app->settings.height);
	}
	else
		SDL_SetWindowFullscreen(app->window->window, 0);
}

void	handle_toggle_debug_mode(t_doom3d *app)
{
	app->is_debug = !app->is_debug;
}

void	handle_toggle_normal_map_mode(t_doom3d *app)
{
	app->settings.is_normal_map = !app->settings.is_normal_map;
	if (app->settings.is_normal_map)
		extend_all_objects_shading_opts(app, e_shading_normal_map);
	else
		remove_all_objects_shading_opts(app, e_shading_normal_map);
}
