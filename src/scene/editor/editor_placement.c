/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_placement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:50:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/30 17:43:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object		*editor_place_light_object(t_doom3d *app)
{
	t_3d_object		*light;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	light = place_scene_object(app, (const char*[3]){
		"assets/models/box.obj", NULL,  NULL}, pos);
	l3d_object_set_shading_opts(light, e_shading_invisible);
	light->type = object_type_light;
	light->params_type = object_type_light;
	editor_objects_invisible_highlight(app);\
	return (light);
}