/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/15 19:35:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void				scene_set_triangle_refs(t_scene *scene)
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

static void				set_scene_collision_tree(t_scene *scene)
{
	scene->triangle_tree = NULL;
	if (scene->num_objects > 0)
	{
		scene_set_triangle_refs(scene);
		l3d_kd_tree_create_or_update(&scene->triangle_tree,
			scene->triangle_ref, scene->num_triangles);
	}
}

/*
** Temporary test object placement & debugging functionality
** Also shows how stuff can be placed into the world
** When things work, scene_asset_files.c should be used to load
** models and textures into the world.
*/

static void		place_test_objects(t_doom3d *app)
{
	app->active_scene->objects[app->active_scene->num_objects++] =
		l3d_object_instantiate(l3d_plane_create(
			l3d_read_bmp_32bit_rgba_surface("assets/textures/Dirs.bmp"),
			NULL),
		app->unit_size, false);
	l3d_3d_object_translate(app->active_scene->objects[0],
		0, app->unit_size, 0);
	// Freeing the texture at free(scene->objects[0]->material->texture->pixels);
	// Because this test texture wasn't loaded into scene->textures hashmap
	// at scene_asset_files.c. // ToDo: Later to be removed
	app->active_scene->objects[app->active_scene->num_objects++] =
		l3d_object_instantiate(l3d_plane_create(
			l3d_read_bmp_32bit_rgba_surface("assets/textures/lava.bmp"),
			NULL),
		app->unit_size, false);
	l3d_3d_object_scale(app->active_scene->objects[1], 10, 10, 10);
	l3d_3d_object_rotate(app->active_scene->objects[1], -90, 0, 0);
	l3d_3d_object_translate(app->active_scene->objects[1],
		0, 2 * app->unit_size, 0);
}

static void		init_scene_world(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		place_test_objects(app);
		set_scene_collision_tree(app->active_scene);
		l3d_skybox_create(app->active_scene->skybox,
			app->active_scene->skybox_textures, app->unit_size);
		player_init(app, (t_vec3){0, 0, 0});
	}
	else if (app->active_scene->scene_id == scene_id_editor)
	{
		place_test_objects(app);
		l3d_skybox_create(app->active_scene->skybox,
			app->active_scene->skybox_textures, app->unit_size);
		player_init(app, (t_vec3){0, 0, 0});
	}
	if (app->active_scene->main_camera)
		update_camera(app);
}

static void		select_scene(void *app_ptr)
{
	t_scene_data		data;
	t_doom3d			*app;

	app = app_ptr;
	app->is_first_render = true;
	if (app->active_scene != NULL)
		scene_destroy(app->active_scene);
	ft_memset(&data, 0, sizeof(data));
	data.scene_id = app->next_scene_id;
	if (data.scene_id == scene_id_main_menu)
		scene_main_menu_data_set(&data);
	else if (data.scene_id == scene_id_main_menu_settings)
		scene_settings_menu_data_set(&data);
	else if (data.scene_id == scene_id_main_game)
		scene_main_game_data_set(&data);
	else if (data.scene_id == scene_id_editor)
		scene_editor_data_set(&data);
	app->active_scene = scene_new(&data);
	init_scene_world(app);
	if (app->active_scene->scene_id == scene_id_editor)
	{
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	else
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	app->is_loading = false;
}

/*
** Initial transformations are set to id, and they change when player moves.
*/

t_scene			*scene_new(t_scene_data *data)
{
	t_scene		*scene;

	error_check(!(scene = (t_scene*)malloc(sizeof(t_scene))),
		"Failed to malloc scene");
	ft_memset(scene, 0, sizeof(*scene));
	scene->scene_id = data->scene_id;
	ft_memcpy(scene->menu_options, data->menu_options,
		sizeof(char*) * data->menu_option_count);
	scene->menu_option_count = data->menu_option_count;
	scene->selected_option = 0;
	scene->main_camera = data->main_camera;
	scene->map_filename = data->map_filename;
	scene->triangle_ref = NULL;
	ft_memset(scene->skybox, 0, sizeof(t_3d_object*) * 6);
	// ToDo: Setup all assets that belong to app in scene_data.c
	// Assets e.g. that can be used to build the map.
	// Assets that are loaded to the game
	if (data->scene_id == scene_id_main_game ||
		data->scene_id == scene_id_editor)
		scene_assets_load(scene, data);
	return (scene);
}

/*
** Concurrently select's and loads next scene. Once done, select scene
** will turn app->is_loading to false;
*/

void			scene_next_select(t_doom3d *app)
{
	app->is_loading = true;
	thread_pool_add_work(app->thread_pool,
		select_scene, app);
}

void			scene_destroy(t_scene *scene)
{
	if (scene->map_filename != NULL)
		ft_strdel(&scene->map_filename);
	if (scene->triangle_tree)
		l3d_kd_tree_destroy(scene->triangle_tree);
	if (scene->textures)
		scene_textures_destroy(scene);
	if (scene->normal_maps)
		scene_normal_maps_destroy(scene);
	if (scene->models)
	{
		free(scene->objects[0]->material->texture->pixels);
		free(scene->objects[1]->material->texture->pixels);
		scene_models_destroy(scene);
	}
	if (scene->skybox[0])
		scene_skybox_destroy(scene);
	if (scene->triangle_ref)
	{
		free(scene->triangle_ref);
		scene->triangle_ref = NULL;
	}
	scene_objects_destroy(scene);
	scene_camera_destroy(scene);
	free(scene);
	scene = NULL;
	return ;
}

void			scene_debug(t_scene *scene)
{
	int		i;

	ft_printf("Scene: %d\n"
	"objects: %d\n",
		scene->scene_id,
		scene->num_objects);
	i = -1;
	while (++i < (int)scene->num_objects)
	{
		l3d_3d_object_debug_print(scene->objects[i]);
	}
}
