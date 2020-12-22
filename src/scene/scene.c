/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/22 15:06:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		select_scene(void *app_ptr)
{
	t_doom3d			*app;

	SDL_StopTextInput();
	app = app_ptr;
	app->is_first_render = true;
	if (app->active_scene != NULL)
		scene_destroy(app->active_scene);
	app->active_scene = scene_new(app->next_scene_id);
	active_scene_content_set(app);
	app->is_loading = false;
}

/*
** Initial transformations are set to id, and they change when player moves.
*/

t_scene			*scene_new(t_scene_id scene_id)
{
	t_scene		*scene;

	error_check(!(scene = (t_scene*)malloc(sizeof(t_scene))),
		"Failed to malloc scene");
	ft_memset(scene, 0, sizeof(*scene));
	scene->scene_id = scene_id;
	scene->triangle_ref = NULL;
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

	scene_menus_destroy(scene);
	if (scene->triangle_tree)
		l3d_kd_tree_destroy(scene->triangle_tree);
	if (scene->textures)
		scene_textures_destroy(scene);
	if (scene->normal_maps)
		scene_normal_maps_destroy(scene);
	if (scene->models)
		scene_models_destroy(scene);
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
