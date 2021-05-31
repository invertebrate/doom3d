/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/06/01 00:39:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Initialize scene_id_main_game
*/

static void	scene_game_init(t_doom3d *app)
{
	t_3d_object		*start;
	t_3d_object		*end;

	l3d_skybox_create(app->active_scene->skybox,
		app->assets.skybox_textures, app->unit_size);
	read_map(app, app->level_list[app->current_level]);
	start = find_one_object_by_type(app, object_type_trigger,
			trigger_player_start);
	end = find_one_object_by_type(app, object_type_trigger, trigger_player_end);
	error_check(!start || !end, "Invalid map: No start or end found in map");
	editor_objects_non_culled_unhighlight(app);
	editor_objects_invisible_unhighlight(app);
	app->settings.is_third_person = false;
	app->active_scene->third_person_camera_distance = 3 * app->unit_size;
	player_init(app, (t_vec3){start->position[0],
		start->position[1] - 0.5 * app->player.player_height,
		start->position[2]});
	weapons_init(app);
	path_node_network_init(app);
	player_animations_init(app);
	set_player_default_frame(app);
	projectile_data_init(app);
	window_3d_framebuffer_recreate(app->window,
		(int32_t[2]){app->window->framebuffer->width - 192,
		app->window->framebuffer->height - 108}, (int32_t[2]){96, 32});
}

/*
** Initialize scene for editor
*/

static void	scene_editor_init(t_doom3d *app)
{
	editor_deselect_all(app);
	app->editor.is_moving = false;
	app->settings.is_third_person = false;
	if (!app->level_list[app->editor.editor_level] && !app->editor.is_new_map)
		editor_init(app, 0);
	if (app->level_list[app->editor.editor_level])
	{
		if (app->level_list[app->editor.editor_level])
			read_map(app, app->level_list[app->editor.editor_level]);
		editor_objects_invisible_highlight(app);
		editor_objects_non_culled_highlight(app);
		app->editor.is_saved = true;
	}
	else
	{
		app->editor.is_saved = false;
		app->editor.is_new_map = false;
	}
	app->editor.editor_menu_id = editor_menu_none;
	app->editor.editor_menu = NULL;
	editor_player_init(app);
	window_3d_framebuffer_recreate(app->window,
		(int32_t[2]){app->window->framebuffer->width - 168,
		app->window->framebuffer->height - 64}, (int32_t[2]){158, 10});
}

static void	active_scene_init(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		scene_game_init(app);
		active_scene_update_after_objects(app);
		init_sprite_effect_timers(app);
		LOG_INFO("Initialized Game Scene with %d objects",
			app->active_scene->num_objects);
		if (app->current_level == 0)
		{
			ft_memset(&app->stats, 0, sizeof(t_stats));
			LOG_INFO("Reset stats (First Level)");
		}
		app->stats.level_start_time = SDL_GetTicks();
	}
	else if (app->active_scene->scene_id == scene_id_editor3d)
	{
		scene_editor_init(app);
		active_scene_update_after_objects(app);
		LOG_INFO("Initialized Editor Scene at %d objects",
			app->active_scene->num_objects);
	}
}

static void	active_scene_mouse_mode_set(t_doom3d *app)
{
	if (app->active_scene->scene_id != scene_id_main_game)
	{
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}

/*
** Set textures, normal maps, and other assets for active scene
*/

void	active_scene_content_set(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game
		|| app->active_scene->scene_id == scene_id_editor3d)
	{
		LOG_INFO("Create Texture Hash Map");
		app->active_scene->object_textures
			= hash_map_create(MAX_NUM_OBJECTS);
		LOG_INFO("Create Normal Map Hash Map");
		app->active_scene->object_normal_maps
			= hash_map_create(MAX_NUM_OBJECTS);
		LOG_INFO("Create Object Timer Hash Map");
		app->active_scene->object_timers = hash_map_create(128);
		LOG_INFO("Create Camera");
		app->active_scene->main_camera = new_camera();
		app->active_scene->third_person_camera = new_camera();
		error_check(!app->active_scene->main_camera, "Camera NULL");
		error_check(!app->active_scene->third_person_camera, "Camera NULL");
	}
	active_scene_mouse_mode_set(app);
	active_scene_init(app);
	LOG_INFO("Create Scene Menus");
	active_scene_menus_create(app);
}
