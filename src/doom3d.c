/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/19 16:42:47 by ohakola          ###   ########.fr       */
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
	if (app->active_scene->scene_id != app->next_scene_id ||
		app->is_scene_reload)
		scene_next_select(app);
}

static void		doom3d_main_loop(t_doom3d *app)
{
	while (app->is_running)
	{
		app->info.performance_start = SDL_GetPerformanceCounter();
		if (app->window->resized)
			resize_dependent_recreate(app);
		window_frame_clear(app->window);
		handle_scene_switch(app);
		doom3d_events_handle(app);
		doom3d_update_objects(app);
		doom3d_player_animation_update(app);
		doom3d_render(app);
		window_frame_draw(app->window);
		doom3d_notifications_update(app);
		doom3d_debug_info_capture(app);
	}
}

void			settings_init(t_doom3d *app)
{
	app->settings.is_normal_map = false;
	app->settings.is_skybox = true;
	app->settings.width = 1280;
	app->settings.height = 720;
}

void			doom3d_init(t_doom3d *app)
{
	app->active_scene = NULL;
	app->is_running = true;
	app->is_debug = true;
	app->is_scene_reload = false;
	app->unit_size = app->window->width;
	app->next_scene_id = scene_id_main_menu;
	ft_memset(&app->notifications, 0, sizeof(app->notifications));
	read_level_list(app);
	app->current_level = 0;
	editor_init(app, 0);
	scene_next_select(app);
}

static void		doom3d_cleanup(t_doom3d *app)
{
	int32_t		i;

	thread_pool_destroy(app->thread_pool);
	scene_destroy(app);
	window_destroy(app->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	i = -1;
	while (++i < (int32_t)app->num_levels)
		ft_strdel(&app->level_list[i]);
	doom3d_notifications_delete_all(app);
}

void			doom3d_run(t_doom3d *app)
{
	int32_t	cpu_count;

	cpu_count = SDL_GetCPUCount();
	app->thread_pool = thread_pool_create(
		cpu_count >= NUM_THREADS_DEFAULT ? cpu_count : NUM_THREADS_DEFAULT);
	error_check(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
	error_check(TTF_Init() == -1, TTF_GetError());
	settings_init(app);
	window_create(&app->window, app->settings.width, app->settings.height);
	doom3d_init(app);
	doom3d_main_loop(app);
	doom3d_cleanup(app);
}
