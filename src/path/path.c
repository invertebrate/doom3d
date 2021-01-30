/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 22:21:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/30 09:38:21 by ohakola          ###   ########.fr       */
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
	//After a node is added, reform the paths
	path_objects_set_neighbors(app);
}

/*
** Connects t_path_node params inside t_3d_object so that they point
** to their nearest neighbors
** Then npcs can loop those to find where to move :)
*/

void			path_objects_set_neighbors(t_doom3d *app)
{
	ft_printf("ToDo: Fill contens of path_objects_set_neighbors function\n");
	(void)app;
	//Some logic to loop all t_3d_obj that are of type object_type_path
	//And access their params and set the neighbors be other 3d objects
	//of object_type_path
	//After this works, we can debug / connect lines in editor to show connected
	//nodes
}
