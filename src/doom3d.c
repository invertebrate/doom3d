/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/28 18:34:50 by ohakola          ###   ########.fr       */
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
		active_scene_menu_recreate(app);
		app->is_first_render = true;
	}
}

static void		handle_scene_switch(t_doom3d *app)
{
	if (!app->is_loading &&
		app->active_scene->scene_id != app->next_scene_id)
		scene_next_select(app);
}

static void		doom3d_main_loop(t_doom3d *app)
{
	while (app->is_running)
	{
		app->info.performance_start = SDL_GetPerformanceCounter();
		update_app_ticks(app);
		if (app->window->resized)
			resize_dependent_recreate(app);
		handle_scene_switch(app);
		window_frame_clear(app->window);
		if (app->is_loading)
		{
			loading_render(app);
			window_frame_draw(app->window);
			doom3d_debug_info_capture(app);
			continue ;
		}
		else
			events_handle(app);
		doom3d_render(app);
		if (app->is_debug)
			doom3d_debug_info_render(app);
		window_frame_draw(app->window);
		doom3d_debug_info_capture(app);
		ft_printf("%u\n", app->current_tick);
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
	app->editor.is_saving = false;
	app->editor.is_saved = false;
	read_level_list(app);
	app->current_level = 0;
	app->editor.editor_level = 0;
	app->current_tick = 0;
	ft_memset(app->editor.editor_filename, 0,
		sizeof(app->editor.editor_filename));
	ft_memset(app->editor.selected_object_str, 0,
		sizeof(app->editor.selected_object_str));
	ft_memcpy(app->editor.editor_filename, app->level_list[app->current_level],
		ft_strlen(app->level_list[app->current_level]));
	scene_next_select(app);
}

static void		doom3d_cleanup(t_doom3d *app)
{
	int32_t		i;

	thread_pool_destroy(app->thread_pool);
	scene_destroy(app->active_scene);
	window_destroy(app->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	i = -1;
	while (++i < (int32_t)app->num_levels)
		ft_strdel(&app->level_list[i]);
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
	doom3d_main_loop(app);
	doom3d_cleanup(app);
}
