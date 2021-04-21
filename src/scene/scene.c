/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/19 00:15:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		select_scene(t_doom3d *app)
{
	SDL_StopTextInput();
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
t_scene			*scene_new(t_scene_id scene_id)
{
	t_scene		*scene;

	error_check(!(scene = (t_scene*)ft_calloc(sizeof(t_scene))),
		"Failed to malloc scene");
	ft_memset(scene, 0, sizeof(*scene));
	ft_memset(scene->deleted_object_i, 0, sizeof(scene->deleted_object_i));
	scene->num_deleted = 0;
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
void			select_next_scene(t_doom3d *app)
{
	LOG_INFO("Select Scene %d", app->next_scene_id);
	window_frame_clear(app->window);
	render_loading_view(app);
	draw_window_frame(app->window);
	select_scene(app);
}

/*
** Destroy scene
*/
void			scene_destroy(t_doom3d *app)
{
	active_scene_popup_menu_destroy(app);
	scene_menus_destroy(app->active_scene);
	if (app->active_scene->triangle_tree)
		l3d_kd_tree_destroy(app->active_scene->triangle_tree);
	if (app->active_scene->textures)
		scene_textures_destroy(app->active_scene);
	if (app->active_scene->normal_maps)
		scene_normal_maps_destroy(app->active_scene);
	if (app->active_scene->models)
		scene_assets_destroy(app->active_scene);
	if (app->active_scene->skybox[0])
		scene_skybox_destroy(app->active_scene);
	if (app->active_scene->triangle_ref)
	{
		free(app->active_scene->triangle_ref);
		app->active_scene->triangle_ref = NULL;
	}
	//call destroy frames function
	scene_objects_destroy(app->active_scene);
	scene_camera_destroy(app->active_scene);
	free(app->active_scene);
	app->active_scene = NULL;
	return ;
}
