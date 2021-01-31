/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:21:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/31 16:07:27 by ahakanen         ###   ########.fr       */
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
	path.parent = path_obj;
	l3d_3d_object_set_params(path_obj,
		&path, sizeof(t_path_node), object_type_path);
}

/*
** Place path object in scene (via editor)
*/

void				place_path_object(t_doom3d *app)
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

static void			path_draw_individual_node_connections(t_render_work *work, t_3d_object *obj)
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
		draw_debug_line(work->app, work->framebuffer->sub_buffers[work->sub_buffer_i],
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

static t_path_node	*path_check_existing(t_doom3d *app, t_path_node *path_obj)
{
	t_path_node	*ret;
	int			i;

	i = path_obj->neighbourcount;
	while (--i > -1)
	{
		if (!path_obj->neighbors[i])	// skipping nulls in case a node connection has been deleted
			continue;
		if (path_obj->neighbors[i] == app->editor.selected_object)
			return ((ret = app->editor.selected_object->params));
	}
	return (NULL);
}

/*
** Deletes all connections of a node
** eg. for deletion of a node object
*/

void				delete_path_object_connections(t_path_node *src)
{
	t_path_node	*dst;
	int			i;

	i = src->neighbourcount;
	while (--i > -1)
		path_delete_connection(src, (dst = src->neighbors[i]->params));
}

/*
** Deletes the connection between two path nodes,
** then moves any nodes after the deleted nodes
** to fill the spot and updates neighbour counts of both nodes
*/

void				path_delete_connection(t_path_node *src,
											t_path_node *dst)
{
	int	i;
	int	j;

	i = src->neighbourcount;
	j = dst->neighbourcount;
	while (--i > 0)
		if (src->neighbors[i] == dst->parent)
			break ;
	while (--j > 0)
		if (dst->neighbors[j] == src->parent)
			break ;
	while (++i < src->neighbourcount)
		src->neighbors[i - 1] = src->neighbors[i];
	while (++j < dst->neighbourcount)
		dst->neighbors[j - 1] = dst->neighbors[j];
	src->neighbourcount--;
	dst->neighbourcount--;;
	ft_printf("deleted connection between obj %d and obj %d!\n", src->parent->id, dst->parent->id);//test
}

/*
** Connects t_path_node params inside t_3d_object so that they point
** to their nearest neighbors
** Then npcs can loop those to find where to move :)
*/

void				path_objects_set_neighbour(t_doom3d *app, t_3d_object *obj)
{
	t_path_node	*path_obj;
	t_path_node	*dest;
	t_path_node	*delete;

	if (obj == NULL)
		return ;
	path_obj = obj->params;
	dest = app->editor.selected_object->params;
	if (path_obj->neighbourcount >= PATH_NEIGHBOUR_MAX)
		ft_printf("path connection limit reached on source!\n");
	else if (dest->neighbourcount >= PATH_NEIGHBOUR_MAX)
		ft_printf("path connection limit reached on destination!\n");
	else if (path_obj == dest)
		ft_printf("cannot connect to itself!\n");
	else if ((delete = path_check_existing(app, path_obj)) != NULL)
		path_delete_connection(path_obj, delete);
	else
	{
		path_obj->neighbors[path_obj->neighbourcount] = app->editor.selected_object;
		dest->neighbors[dest->neighbourcount] = obj;
		path_obj->neighbourcount++;
		dest->neighbourcount++;
		ft_printf("nodes connected successfully!\n");
	}
}
