/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:21:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/07 14:31:40 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Initializes path node content to zero under object params
** Called when map is read or when object is placed in editor
*/

void				path_node_init(t_3d_object *path_obj)
{
	t_path_node		path;

	ft_memset(&path, 0, sizeof(t_path_node));
	path.parent_obj = path_obj;
	l3d_3d_object_set_params(path_obj,
		&path, sizeof(t_path_node), object_type_path);
}

/*
** Place path object in scene (via editor)
*/

t_3d_object			*place_path_object(t_doom3d *app)
{
	t_3d_object		*path_obj;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	path_obj = place_scene_object(app, (const char*[3]){
		"assets/models/box.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(path_obj, e_shading_invisible |
		e_shading_cyan | e_shading_transparent);
	path_obj->type = object_type_path;
	l3d_3d_object_scale(path_obj, 0.3, 0.3, 0.3);
	path_node_init(path_obj);
	if (app->editor.selected_objects[0] &&
		app->editor.selected_objects[0]->type == object_type_path &&
		app->keyboard.state[SDL_SCANCODE_LCTRL])
		path_objects_set_neighbour(app, path_obj);
	LOG_INFO("Placed path object %d", path_obj->id);
	return (path_obj);
}

static void			path_draw_individual_node_connections(t_render_work *work,
														t_3d_object *obj)
{
	t_path_node	*node;
	t_vec3		vecs[2];
	int			i;

	node = obj->params;
	i = node->num_neighbors;
	while (--i > -1)
	{
		if (!node->neighbors[i])
			continue;
		ml_vector3_copy(obj->position, vecs[0]);
		ml_vector3_copy(node->neighbors[i]->position, vecs[1]);
		draw_debug_line(work->app,
			work->framebuffer->sub_buffers[work->sub_buffer_i],
			vecs, 0xffff00ff);
	}
}

void				path_draw_connections(t_render_work *work)
{
	int32_t			i;
	t_3d_object		*obj;

	if (work->app->active_scene->scene_id != scene_id_editor3d)
		return ;
	i = -1;
	while (++i < (int32_t)(work->app->active_scene->num_objects +
		work->app->active_scene->num_deleted))
	{
		obj = work->app->active_scene->objects[i];
		if (!obj || obj->type != object_type_path)
			continue ;
		path_draw_individual_node_connections(work, obj);
	}
}
