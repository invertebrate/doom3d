/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:35:01 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Initialize scene_id_main_game
*/

static void	scene_game_init(t_doom3d *app)
{
	t_3d_object		*start;

	l3d_skybox_create(app->active_scene->skybox,
		app->active_scene->skybox_textures, app->unit_size);
	read_map(app, app->level_list[app->current_level]);
	start = find_one_object_by_type(app, object_type_trigger,
			trigger_player_start);
	if (!start || !find_one_object_by_type(app, object_type_trigger,
			trigger_player_end))
	{
		notify_user(app, (t_notification){.message
			= "Map does not have Start or End locations, Add them in editor!",
			.type = notification_type_info, .time = 2000});
		push_custom_event(app, event_scene_change,
			(void *)scene_id_main_menu, NULL);
		return ;
	}
	app->is_third_person = false;
	app->active_scene->third_person_camera_distance = 3 * app->unit_size;
	player_init(app, start->position);
	weapons_init(app);
	path_node_network_init(app);
	player_animations_init(app);
	set_player_default_frame(app);
	projectile_data_init(app);
	active_scene_update_after_objects(app->active_scene);
}

/*
** Initialize scene for editor
*/

static void	scene_editor_init(t_doom3d *app)
{
	editor_deselect_all(app);
	app->editor.is_moving = false;
	app->is_third_person = false;
	if (!app->level_list[app->editor.editor_level] && !app->editor.is_new_map)
		editor_init(app, 0);
	if (app->level_list[app->editor.editor_level])
	{
		if (app->level_list[app->editor.editor_level])
			read_map(app, app->level_list[app->editor.editor_level]);
		editor_objects_invisible_highlight(app);
		app->editor.is_saved = true;
	}
	else
	{
		app->editor.is_saved = false;
		app->editor.is_new_map = false;
	}
	app->editor.editor_menu_id = editor_menu_none;
	app->editor.editor_menu = NULL;
	l3d_skybox_create(app->active_scene->skybox,
		app->active_scene->skybox_textures, app->unit_size);
	active_scene_update_after_objects(app->active_scene);
	player_init(app, (t_vec3){0,
		-10 * app->unit_size, -20 * app->unit_size});
	player_rotate_vertical(app, -90);
}

static void	active_scene_init(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		scene_game_init(app);
		LOG_INFO("Initialized Game Scene with %d objects",
			app->active_scene->num_objects);
	}
	else if (app->active_scene->scene_id == scene_id_editor3d)
	{
		scene_editor_init(app);
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
		LOG_INFO("Create Camera");
		app->active_scene->main_camera = new_camera();
		app->active_scene->third_person_camera = new_camera();
		error_check(!app->active_scene->main_camera, "Camera NULL");
		error_check(!app->active_scene->third_person_camera, "Camera NULL");
		LOG_INFO("Load Assets");
		scene_assets_load(app->active_scene);
	}
	active_scene_mouse_mode_set(app);
	active_scene_init(app);
	LOG_INFO("Create Scene Menus");
	active_scene_menus_create(app);
}
