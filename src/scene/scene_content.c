/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/04 23:55:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool			include_object_in_triangle_tree(t_scene *scene,
							t_3d_object *object)
{
	if (scene->scene_id == scene_id_editor3d)
		return (!!object);
	return (object != NULL &&
			object->type != object_type_trigger &&
			object->type != object_type_light &&
			object->type != object_type_path);
}

static void				active_scene_triangle_refs_set(t_scene *scene)
{
	int32_t		i;
	int32_t		j;
	int32_t		k;
	int32_t		num_triangles;

	if (scene->triangle_ref != NULL)
		free(scene->triangle_ref);
	i = -1;
	num_triangles = 0;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
		if (include_object_in_triangle_tree(scene, scene->objects[i]))
			num_triangles += scene->objects[i]->num_triangles;
	scene->num_triangles = num_triangles;
	error_check(!(scene->triangle_ref =
		ft_calloc(sizeof(t_triangle*) * num_triangles)),
		"Failed to malloc triangle ref");
	i = -1;
	k = 0;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (!include_object_in_triangle_tree(scene, scene->objects[i]))
			continue ;
		j = -1;
		while (++j < scene->objects[i]->num_triangles)
			scene->triangle_ref[k++] = &scene->objects[i]->triangles[j];
	}
}

/*
** Update object bounding boxes
** Update triangle tree
*/

void					active_scene_update_after_objects(t_scene *scene)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (scene->objects[i])
			l3d_object_aabb_update(scene->objects[i]);
	}
	active_scene_triangle_refs_set(scene);
	l3d_kd_tree_create_or_update(&scene->triangle_tree,
		scene->triangle_ref, scene->num_triangles);
}

static void		scene_game_init(t_doom3d *app)
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
		notify_user(app, (t_notification){
			.message =
				"Map does not have Start or End locations, Add them in editor!",
			.type = notification_type_info, .time = 2000});
		push_custom_event(app, event_scene_change,
			(void*)scene_id_main_menu, NULL);
		return ;
	}
	player_init(app, start->position);
	weapons_init(app);
	path_node_network_init(app);
	player_animations_init(app);
	set_player_default_frame(app);
	projectile_data_init(app);
	active_scene_update_after_objects(app->active_scene);
}

static void		scene_editor_init(t_doom3d *app)
{
	editor_deselect_all(app);
	app->editor.is_moving = false;
	if (app->level_list[app->editor.editor_level])
	{
		if (app->level_list[app->editor.editor_level])
			read_map(app, app->level_list[app->editor.editor_level]);
		editor_objects_invisible_highlight(app);
		ft_memcpy(app->editor.editor_savename,
			app->editor.editor_filename,
			ft_strlen(app->editor.editor_savename));
		app->editor.is_saved = true;
	}
	else
		app->editor.is_saved = false;
	app->editor.editor_menu_id = editor_menu_none;
	app->editor.editor_menu = NULL;
	l3d_skybox_create(app->active_scene->skybox,
		app->active_scene->skybox_textures, app->unit_size);
	active_scene_update_after_objects(app->active_scene);
	player_init(app, (t_vec3){0,
		-10 * app->unit_size, -20 * app->unit_size});
	player_rotate_vertical(app, -90);
}

static void		active_scene_init(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		scene_game_init(app);
	}
	else if (app->active_scene->scene_id == scene_id_editor3d)
	{
		scene_editor_init(app);
	}
	if (app->active_scene->main_camera)
		update_camera(app);
}

static void		active_scene_mouse_mode_set(t_doom3d *app)
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

void		active_scene_menu_recreate(t_doom3d *app)
{
	scene_menus_destroy(app->active_scene);
	if (app->active_scene->scene_id == scene_id_main_game)
		pause_menu_create(app);
	else if (app->active_scene->scene_id == scene_id_editor3d)
		editor3d_menu_create(app);
	else if (app->active_scene->scene_id == scene_id_main_menu)
		main_menu_create(app);
	else if (app->active_scene->scene_id == scene_id_main_menu_settings)
		settings_menu_create(app);
}

void		active_scene_content_set(t_doom3d *app)
{

	if (app->active_scene->scene_id == scene_id_main_game ||
		app->active_scene->scene_id == scene_id_editor3d)
	{
		app->active_scene->object_textures =
			hash_map_create(MAX_NUM_OBJECTS);
		app->active_scene->object_normal_maps =
			hash_map_create(MAX_NUM_OBJECTS);
		app->active_scene->main_camera = new_camera();
		scene_assets_load(app->active_scene);
	}
	active_scene_mouse_mode_set(app);
	active_scene_init(app);
	active_scene_menu_recreate(app);
}
