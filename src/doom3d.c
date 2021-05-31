/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/06/01 00:47:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Scene switch should be the first thing we do if next scene id has changed
** in main loop (before event handling).
** Force main game to be smaller resolution.
*/

static void	handle_scene_switch(t_doom3d *app)
{
	t_scene_id	prev_scene_id;

	if (app->active_scene->scene_id != app->next_scene_id
		|| app->is_scene_reload)
	{
		if (app->settings.is_debug)
			LOG_DEBUG("Scen change detected, selecting next");
		prev_scene_id = app->active_scene->scene_id;
		if (app->next_scene_id == scene_id_main_game
			&& prev_scene_id != scene_id_main_game
			&& app->settings.width != WIDTH)
		{
			handle_window_resize(app, WIDTH, HEIGHT);
			resize_dependent_recreate(app);
		}
		select_next_scene(app);
		if (prev_scene_id == scene_id_main_game)
			mp_typec(app, 0, 0, SSTOPPED);
		if (app->active_scene->scene_id == scene_id_main_game)
			push_custom_event(app, event_music_play,
				(void *)mu_main, s_ini(1, 10, st_main_menu, 0.6));
	}
}

static void	app_init(t_doom3d *app)
{
	ft_memset(&app->stats, 0, sizeof(t_stats));
	LOG_INFO("Register Custom Events");
	register_custom_events(app);
	mp_init(app);
	app->active_scene = NULL;
	app->triangles_in_view = 0;
	app->is_running = true;
	app->is_scene_reload = false;
	app->unit_size = app->window->width;
	ft_memset(&app->notifications, 0, sizeof(app->notifications));
	read_level_list(app);
	app->current_level = 0;
	editor_init(app, 0);
	LOG_INFO("Allocating render triangle pool of size %d "
		"And clipped vertices pool of size %d",
		RENDER_TRIANGLE_POOL_SIZE, RENDER_TRIANGLE_POOL_SIZE * 3);
	allocate_render_triangle_pool(app, RENDER_TRIANGLE_POOL_SIZE);
	app->next_scene_id = scene_id_main_menu;
	select_next_scene(app);
}

static void	cleanup(t_doom3d *app)
{
	int32_t		i;

	mp_close(app);
	LOG_INFO("Destroy thread pool");
	thread_pool_destroy(app->thread_pool);
	LOG_INFO("Destroy scene");
	scene_destroy(app);
	LOG_INFO("Destroy assets");
	assets_destroy(&app->assets);
	LOG_INFO("Destroy window");
	window_destroy(app->window);
	LOG_INFO("Quit SDL");
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	i = -1;
	LOG_INFO("Free level strs");
	while (++i < (int32_t)app->num_levels)
		ft_strdel(&app->level_list[i]);
	LOG_INFO("Delete notifications");
	delete_notifications(app);
	LOG_INFO("Destroy render triangle pool & clipped vertices pool");
	destroy_render_triangle_pool(app);
}

static void	main_loop(t_doom3d *app)
{
	uint32_t	clear_color;

	while (app->is_running)
	{
		clear_color = CLEAR_COLOR;
		app->info.performance_start = SDL_GetPerformanceCounter();
		if (app->window->resized)
			resize_dependent_recreate(app);
		handle_scene_switch(app);
		handle_events(app);
		update_player(app);
		update_objects(app);
		window_frame_clear(app->window, clear_color);
		render_to_framebuffer(app);
		draw_window_frame(app->window);
		update_notifications(app);
		capture_fps(app);
		update_app_ticks(app);
		if (app->active_scene->scene_id == scene_id_main_game)
			trigger_timer_update(app);
	}
}

void	doom3d_run(t_doom3d *app)
{
	int32_t	cpu_count;
	int32_t	num_threads;

	assets_load(app);
	cpu_count = SDL_GetCPUCount();
	num_threads = ft_max_int((int32_t[2]){
			NUM_THREADS_DEFAULT, cpu_count}, 2);
	app->thread_pool = thread_pool_create(num_threads);
	LOG_INFO("Created thread pool with %d threads for %d logical cpus",
		num_threads, cpu_count);
	LOG_INFO("Initialize SDL");
	error_check(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0, SDL_GetError());
	error_check(TTF_Init() == -1, TTF_GetError());
	LOG_INFO("Initialize App settings");
	settings_init(app);
	LOG_INFO("Create SDL Window & frame buffers");
	window_create(&app->window, app->settings.width, app->settings.height);
	window_set_fonts(app->window, &app->assets);
	app_init(app);
	main_loop(app);
	cleanup(app);
}
