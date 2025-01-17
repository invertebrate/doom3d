/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/28 12:53:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	set_debug_info(t_doom3d *app, char *debug_info, char *pos)
{
	t_vec3	unit_pos;

	if (app->active_scene->scene_id == scene_id_main_game
		|| app->active_scene->scene_id == scene_id_editor3d)
	{
		ml_vector3_mul(app->player.pos, 1.0 / app->unit_size, unit_pos);
		ml_vector3_to_str(unit_pos, pos);
		ft_sprintf(debug_info, "fps: %u\ndelta time: %u\nunit_pos: %s\n"
			"triangles in view: %d\n"
			"lights: %d",
			app->info.fps, app->info.delta_time, pos, app->triangles_in_view,
			app->active_scene->num_scene_lights);
	}
	else
		ft_sprintf(debug_info, "fps: %u\ndelta time: %u",
			app->info.fps, app->info.delta_time);
}

void	render_debug_info(t_doom3d *app)
{
	char	debug_info[1024];
	char	pos[128];

	ft_memset(debug_info, 0, sizeof(debug_info));
	ft_memset(pos, 0, sizeof(pos));
	set_debug_info(app, debug_info, pos);
	window_text_render_wrapped(app->window, (t_text_params){
		.text = debug_info, .blend_ratio = 1.0, .xy = (int [2]){5, 5},
		.text_color = (SDL_Color){255, 255, 255, 0}},
		app->window->small_font);
}

void	capture_fps(t_doom3d *app)
{
	app->info.performance_end = SDL_GetPerformanceCounter();
	app->info.delta_time
		= (app->info.performance_end - app->info.performance_start) * 1000.0
		/ SDL_GetPerformanceFrequency();
	app->info.fps = window_framerate_capture(app->info.delta_time);
}

/*
** Sometimes full screen alt + tab resizes window wrong, so force it to set size
*/

static void	force_window_size_after_resize_to_match_settings(t_doom3d *app)
{
	SDL_Surface	*surface;

	surface = SDL_GetWindowSurface(app->window->window);
	if (surface->w != app->settings.width
		|| surface->h != app->settings.height)
	{
		if (app->settings.is_debug)
			LOG_DEBUG("Window size wrong %d %d force to %d %d",
				surface->w, surface->h,
				app->settings.width, app->settings.height);
		window_resize(app->window, app->settings.width, app->settings.height);
		app->window->resized = false;
	}
}

void	resize_dependent_recreate(t_doom3d *app)
{
	SDL_Event	event;

	app->window->resized = false;
	if (app->window->is_hidden)
	{
		if (app->settings.is_debug)
			LOG_DEBUG("Window hidden, ignoring all but quit event");
		while (app->window->is_hidden)
		{
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT)
			{
				push_custom_event(app, event_quit, NULL, NULL);
				break ;
			}
		}
	}
	else
	{
		force_window_size_after_resize_to_match_settings(app);
		window_frame_recreate(app->window);
		scene_menus_destroy(app->active_scene);
		active_scene_menus_create(app);
	}
}
