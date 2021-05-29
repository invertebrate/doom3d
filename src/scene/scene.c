/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 22:11:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	select_scene(t_doom3d *app)
{
	SDL_StopTextInput();
	delete_notifications_of_type(app, notification_type_story);
	delete_notifications_of_type(app, notification_type_info);
	if (app->active_scene != NULL)
	{
		LOG_INFO("Destroy previous scene %d", app->active_scene->scene_id);
		scene_destroy(app);
	}
	app->active_scene = scene_new(app->next_scene_id);
	LOG_INFO("Set Scene Content");
	active_scene_content_set(app);
	app->is_scene_reload = false;
}

/*
** Initial transformations are set to id, and they change when player moves.
*/

t_scene	*scene_new(t_scene_id scene_id)
{
	t_scene		*scene;

	error_check(!(scene = (t_scene *)ft_calloc(sizeof(t_scene))),
		"Failed to malloc scene");
	ft_memset(scene, 0, sizeof(*scene));
	ft_memset(scene->free_object_indices, -1,
		sizeof(scene->free_object_indices));
	scene->num_free_indices = 0;
	scene->num_objects = 0;
	scene->npc_update_timer = 0;
	scene->last_object_index = -1;
	scene->scene_id = scene_id;
	scene->triangle_ref = NULL;
	scene->temp_objects = NULL;
	return (scene);
}

/*
** Selects next scene by app->next_scene_id
*/

void	select_next_scene(t_doom3d *app)
{
	LOG_INFO("Select Scene %d", app->next_scene_id);
	window_frame_clear(app->window, 0x000000ff);
	render_loading_view(app);
	draw_window_frame(app->window);
	select_scene(app);
}

static void	scene_objects_destroy(t_scene *scene)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(scene->num_objects + scene->num_free_indices))
	{
		if (scene->objects[i] != NULL)
		{
			if (scene->objects[i]->type == object_type_npc)
				npc_destroy(scene->objects[i]);
			else
				l3d_3d_object_destroy(scene->objects[i]);
		}
	}
	l3d_temp_objects_destroy(&scene->temp_objects);
	hash_map_destroy(scene->object_normal_maps);
	hash_map_destroy(scene->object_textures);
}

/*
** Destroy scene
*/

void	scene_destroy(t_doom3d *app)
{
	int32_t		i;

	active_scene_popup_menu_destroy(app);
	scene_menus_destroy(app->active_scene);
	if (app->active_scene->scene_id == scene_id_editor3d
		|| app->active_scene->scene_id == scene_id_main_game)
	{
		l3d_kd_tree_destroy(app->active_scene->triangle_tree);
		if (app->active_scene->triangle_ref)
		{
			free(app->active_scene->triangle_ref);
			app->active_scene->triangle_ref = NULL;
		}
		scene_objects_destroy(app->active_scene);
		scene_cameras_destroy(app->active_scene);
	}
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		i = -1;
		while (++i < 6)
			l3d_3d_object_destroy(app->active_scene->skybox[i]);
	}
	free(app->active_scene);
	app->active_scene = NULL;
}
