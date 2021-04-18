/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 20:05:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		set_debug_info(t_doom3d *app, char *debug_info, char *pos)
{
	t_vec3	unit_pos;

	if (app->active_scene->scene_id == scene_id_main_game ||
		app->active_scene->scene_id == scene_id_editor3d)
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

void			render_debug_info(t_doom3d *app)
{
	char	debug_info[1024];
	char	pos[128];

	ft_memset(debug_info, 0, sizeof(debug_info));
	ft_memset(pos, 0, sizeof(pos));
	set_debug_info(app, debug_info, pos);
	window_text_render_wrapped(app->window, (t_text_params){
		.text = debug_info, .blend_ratio = 1.0, .xy = (int[2]){5, 5},
		.text_color = (SDL_Color){255, 255, 255, 0}},
		app->window->debug_font);
}

void			capture_fps(t_doom3d *app)
{
	app->info.performance_end = SDL_GetPerformanceCounter();
	app->info.delta_time =
		(app->info.performance_end - app->info.performance_start) * 1000.0 /
		SDL_GetPerformanceFrequency();
	app->info.fps = window_framerate_capture(app->info.delta_time);
}

uint64_t		performance_counter_start(void)
{
	return (SDL_GetPerformanceCounter());
}

/*
** Usage:
** uint64_t	start = performance_counter_start();
** // Do stuff here
** performance_counter_end(start, "What I did?", 10.0); // where
** // 10.0 is to only print out a result when time diff is > 10ms
** // At 0.0, result is always printed
*/
void			performance_counter_end(uint64_t start_time,
					char *task_name, float delta_limit)
{
	float			delta_time;

	delta_time = (float)(SDL_GetPerformanceCounter() -
		start_time) * 1000.0 /
		(float)SDL_GetPerformanceFrequency();
	if (delta_limit == 0.0 || delta_time > delta_limit)
		LOG_TRACE("%s: Profiler time: %f", task_name, delta_time);
}


void			resize_dependent_recreate(t_doom3d *app)
{
	SDL_Event	event;

	app->window->resized = false;
	if (app->window->is_hidden)
	{
		LOG_INFO("Window hidden, ignoring all but quit event");
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
		window_frame_recreate(app->window);
		active_scene_menu_recreate(app);
	}
}
