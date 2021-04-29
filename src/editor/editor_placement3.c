/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_placement3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:54:24 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/27 01:59:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object			*place_window_wall_prefab(t_doom3d *app)
{
	t_3d_object		*object;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	object = place_scene_object(app, (const char*[3]){
		"assets/models/window/window_wall.obj",
		"assets/textures/window_wall.bmp",
		"assets/textures/window_wall_normal.bmp"}, pos);
	l3d_3d_object_rotate(object, 0, 180, 180);
	object->material->shading_opts = e_shading_transparent;
	placement_notification(app, "Placing window wall!");
	return (object);
}

t_3d_object			*place_lava_plane_prefab(t_doom3d *app)
{
	t_3d_object		*model;
	t_3d_object		*object;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	model = l3d_plane_create(NULL, NULL);
	object = place_procedural_scene_object(app, model, (const char*[2]){
		"assets/textures/lava_molten.bmp", NULL},
		pos);
	l3d_3d_object_destroy(model);
	object->material->shading_opts = e_shading_luminous | e_shading_uv_repeat;
	placement_notification(app, "Placing plane!");
	return (object);
}
