/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 16:36:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		select_scene(t_doom3d *app)
{
	SDL_StopTextInput();
	app->is_first_render = true;
	if (app->active_scene != NULL)
		scene_destroy(app);
	app->active_scene = scene_new(app->next_scene_id);
	active_scene_content_set(app);
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

void			scene_next_select(t_doom3d *app)
{
	window_frame_clear(app->window);
	loading_render(app);
	window_frame_draw(app->window);
	select_scene(app);
}

void			scene_destroy(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		if (app->editor.editor_menu != NULL)
		{
			button_popup_menu_destroy(app->editor.editor_menu);
			app->editor.editor_menu_id = editor_menu_none;
			app->editor.editor_menu = NULL;
		}
	}
	scene_menus_destroy(app->active_scene);
	if (app->active_scene->triangle_tree)
		l3d_kd_tree_destroy(app->active_scene->triangle_tree);
	if (app->active_scene->textures)
		scene_textures_destroy(app->active_scene);
	if (app->active_scene->normal_maps)
		scene_normal_maps_destroy(app->active_scene);
	if (app->active_scene->models)
		scene_models_destroy(app->active_scene);
	if (app->active_scene->skybox[0])
		scene_skybox_destroy(app->active_scene);
	if (app->active_scene->triangle_ref)
	{
		free(app->active_scene->triangle_ref);
		app->active_scene->triangle_ref = NULL;
	}
	scene_objects_destroy(app->active_scene);
	scene_camera_destroy(app->active_scene);
	free(app->active_scene);
	app->active_scene = NULL;
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
