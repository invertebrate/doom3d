/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:21:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/30 23:30:12 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Initializes path node content to zero under object params
** Called when map is read or when object is placed in editor
*/

void			path_node_init(t_3d_object *path_obj)
{
	t_path_node		path;
	
	ft_memset(&path, 0, sizeof(t_path_node));
	l3d_3d_object_set_params(path_obj,
		&path, sizeof(t_path_node), object_type_path);
}

/*
** Place path object in scene (via editor)
*/

void			place_path_object(t_doom3d *app)
{
	t_3d_object		*path_obj;
	t_vec3			pos;

	editor_place_position(app, pos);
	place_scene_object(app, (const char*[3]){
		"assets/models/box.obj", NULL,  NULL}, pos);
	path_obj =
		app->active_scene->objects[app->active_scene->last_object_index];
	l3d_object_set_shading_opts(path_obj, e_shading_invisible);
	path_obj->type = object_type_path;
	l3d_3d_object_scale(path_obj, 0.3, 0.3, 0.3);
	path_node_init(path_obj);
	//After a node is added, if holding LCTRL, connect to last selected node
	if (app->editor.selected_object &&
		app->editor.selected_object->type == object_type_path &&
		app->keyboard.state[SDL_SCANCODE_LCTRL])
		path_objects_set_neighbour(app, path_obj);
}

static void		path_draw_individual_node_connections(t_render_work *work, t_3d_object *obj)
{
	t_path_node	*node;
	t_vec3		vecs[2];
	int			i;

	node = obj->params;
	i = node->neighbourcount;
	while (--i > -1)
	{
		if (!node->neighbors[i])	// skipping nulls in case a node connection has been deleted
			continue;
		ml_vector3_copy(obj->position, vecs[0]);
		ml_vector3_copy(node->neighbors[i]->position, vecs[1]);
		ft_printf("obj->id = %d, i = %d, src = {%f, %f, %f}, dst = {%f, %f, %f}\n", obj->id, i, vecs[0][0], vecs[0][1], vecs[0][2], vecs[1][0], vecs[1][1], vecs[1][2]);//test
		draw_debug_line(work->app, work->framebuffer->sub_buffers[work->sub_buffer_i],
			vecs, 0xffff00ff);
	}
}

void			path_draw_connections(t_render_work *work)
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

/*
** Connects t_path_node params inside t_3d_object so that they point
** to their nearest neighbors
** Then npcs can loop those to find where to move :)
*/

void			path_objects_set_neighbour(t_doom3d *app, t_3d_object *obj)
{
	t_path_node	*path_obj;
	t_path_node	*dest;

	path_obj = obj->params;
	dest = app->editor.selected_object->params;
	if (path_obj->neighbourcount >= PATH_NEIGHBOUR_MAX)
		ft_printf("path connection limit reached on source!\n");
	else if (dest->neighbourcount >= PATH_NEIGHBOUR_MAX)
		ft_printf("path connection limit reached on destination!\n");
	else
	{
		path_obj->neighbors[path_obj->neighbourcount] = app->editor.selected_object;
		dest->neighbors[dest->neighbourcount] = obj;
		path_obj->neighbourcount++;
		dest->neighbourcount++;
		ft_printf("nodes connected successfully!\n");
	}
	//Some logic to loop all t_3d_obj that are of type object_type_path
	//And access their params and set the neighbors be other 3d objects
	//of object_type_path
	//After this works, we can debug / connect lines in editor to show connected
	//nodes
}
