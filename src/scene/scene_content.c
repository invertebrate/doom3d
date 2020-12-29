/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/29 14:35:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void				active_scene_triangle_refs_set(t_scene *scene)
{
	int		i;
	int		j;
	int		k;
	int		num_triangles;

	if (scene->triangle_ref != NULL)
		free(scene->triangle_ref);
	i = -1;
	num_triangles = 0;
	while (++i < (int)scene->num_objects)
		num_triangles += scene->objects[i]->num_triangles;
	scene->num_triangles = num_triangles;
	error_check(!(scene->triangle_ref =
		malloc(sizeof(t_triangle*) * num_triangles)),
		"Failed to malloc triangle ref");
	i = -1;
	k = 0;
	while (++i < (int)scene->num_objects)
	{
		j = -1;
		while (++j < scene->objects[i]->num_triangles)
			scene->triangle_ref[k++] = &scene->objects[i]->triangles[j];
	}
}

static void				active_scene_triangle_tree_set(t_scene *scene)
{
	scene->triangle_tree = NULL;
	if (scene->num_objects > 0)
	{
		active_scene_triangle_refs_set(scene);
		l3d_kd_tree_create_or_update(&scene->triangle_tree,
			scene->triangle_ref, scene->num_triangles);
	}
}

/*
** //! Just an example how you can place test objects
*/

static void				place_test_objects(t_doom3d *app)
{
	place_object(app, (const char*[3]){
		"assets/models/box.obj",
		"assets/textures/rock.bmp", NULL}, (t_vec3){0, app->unit_size, 0});
	ft_printf("Placed test objects\n");
}

static void		game_init(t_doom3d *app)
{
	read_map(app, app->level_list[app->current_level]);
	// Add test objects for playing
	place_test_objects(app);
	active_scene_triangle_tree_set(app->active_scene);
	l3d_skybox_create(app->active_scene->skybox,
		app->active_scene->skybox_textures, app->unit_size);
	player_init(app, (t_vec3){0, 0, 0});
}

static void		editor_init(t_doom3d *app)
{
	app->editor.selected_object = NULL;
	if (app->level_list[app->editor.editor_level])
	{
		read_map(app, app->level_list[app->editor.editor_level]);
		ft_memcpy(app->editor.editor_savename,
			app->editor.editor_filename,
			ft_strlen(app->editor.editor_savename));
		app->editor.is_saved = true;
	}
	else
		app->editor.is_saved = false;
	l3d_skybox_create(app->active_scene->skybox,
		app->active_scene->skybox_textures, app->unit_size);
	active_scene_triangle_tree_set(app->active_scene);
	player_init(app, (t_vec3){0,
		-10 * app->unit_size, -20 * app->unit_size});
	player_rotate_vertical(app, -90);
}

static void		active_scene_init(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		game_init(app);
	}
	else if (app->active_scene->scene_id == scene_id_editor3d)
	{
		editor_init(app);
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
