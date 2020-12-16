/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/16 16:12:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		resize_dependent_recreate(t_doom3d *app)
{
	app->window->resized = false;
	if (app->window->is_hidden)
	{
		while (app->window->is_hidden)
			SDL_PollEvent(NULL);
	}
	else
	{
		window_frame_recreate(app->window);
		app->is_first_render = true;
	}
}

static void		doom3d_main_loop(t_doom3d *app)
{
	while (app->is_running)
	{
		app->info.performance_start = SDL_GetPerformanceCounter();
		if (app->window->resized)
			resize_dependent_recreate(app);
		window_frame_clear(app->window);
		if (app->is_loading)
		{
			loading_render(app);
			window_frame_draw(app->window);
			doom3d_debug_info_capture(app);
			continue ;
		}
		//ToDo Events includes app logic:
		events_handle(app);
		if (app->is_loading)
			continue ;
		doom3d_render(app);
		if (app->is_debug)
			doom3d_debug_info_render(app);
		window_frame_draw(app->window);
		doom3d_debug_info_capture(app);
	}
}

void			doom3d_init(t_doom3d *app)
{
	app->active_scene = NULL;
	app->is_running = true;
	app->is_debug = true;
	app->is_loading = true;
	app->is_minimap_largened = false;
	app->unit_size = app->window->width;
	app->next_scene_id = scene_id_main_menu;
	app->is_normal_map = false;
	scene_next_select(app);
}

static void		doom3d_cleanup(t_doom3d *app)
{
	thread_pool_destroy(app->thread_pool);
	scene_destroy(app->active_scene);
	window_destroy(app->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void			doom3d_run(t_doom3d *app)
{
	int32_t	cpu_count;

	cpu_count = SDL_GetCPUCount();
	app->thread_pool = thread_pool_create(
		cpu_count >= NUM_THREADS_DEFAULT ? cpu_count : NUM_THREADS_DEFAULT);
	error_check(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
	error_check(TTF_Init() == -1, TTF_GetError());
	window_create(&app->window, WIDTH, HEIGHT);
	doom3d_init(app);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom3d_main_loop(app);
	doom3d_cleanup(app);
}
