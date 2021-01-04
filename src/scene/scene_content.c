/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/04 15:16:17 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

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
		if (scene->objects[i] != NULL)
			num_triangles += scene->objects[i]->num_triangles;
	scene->num_triangles = num_triangles;
	error_check(!(scene->triangle_ref =
		malloc(sizeof(t_triangle*) * num_triangles)),
		"Failed to malloc triangle ref");
	i = -1;
	k = 0;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (scene->objects[i] == NULL)
			continue ;
		j = -1;
		while (++j < scene->objects[i]->num_triangles)
			scene->triangle_ref[k++] = &scene->objects[i]->triangles[j];
	}
}

void					active_scene_update_after_objects(t_scene *scene)
{
	active_scene_triangle_refs_set(scene);
	l3d_kd_tree_create_or_update(&scene->triangle_tree,
		scene->triangle_ref, scene->num_triangles);
}

/*
** //! Just an example how you can place test objects
*/

static void				place_test_objects(t_doom3d *app)
{
	//place_object(app, (const char*[3]){
	//	"assets/models/box.obj",
	//	"assets/textures/rock.bmp", NULL}, (t_vec3){0, app->unit_size, 0});
	//ft_printf("Placed test objects\n");

	/*
	NPC TESTING
	*/
	npc_controller_init(app);
	npc_spawn(app, (t_vec3){0, app->unit_size, 0}, 45, 0);
	npc_spawn(app, (t_vec3){app->unit_size * 6, app->unit_size * 5, 0}, 0, 0);
	npc_spawn(app, (t_vec3){app->unit_size * 8, 0, 0}, 90, 0);
	npc_spawn(app, (t_vec3){0, 0, app->unit_size * 6}, 45, 0);
	place_scene_object(app, (const char*[3]){
		"assets/models/box.obj",
		"assets/textures/rock.bmp", NULL}, (t_vec3){0, app->unit_size, 0});
	ft_printf("Placed test objects\n");
}

static void		game_init(t_doom3d *app)
{
	read_map(app, app->level_list[app->current_level]);
	// Add test objects for playing
	place_test_objects(app);
	active_scene_update_after_objects(app->active_scene);
	l3d_skybox_create(app->active_scene->skybox,
		app->active_scene->skybox_textures, app->unit_size);
	player_init(app, (t_vec3){0, 0, 0});
}

static void		editor_init(t_doom3d *app)
{
	app->editor.selected_object = NULL;
	app->editor.is_moving = false;
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
