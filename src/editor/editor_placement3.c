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

t_3d_object			*place_window_glass_prefab(t_doom3d *app)
{
	t_3d_object		*object;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	object = place_scene_object(app, (const char*[3]){
		"assets/models/window/window_glass.obj",
		"assets/textures/glass_texture_30.bmp", NULL}, pos);
	object->material->shading_opts = e_shading_transparent |
		e_shading_uv_repeat;
	placement_notification(app, "Placing window glass!");
	return (object);
}

t_3d_object			*place_window_wall_prefab(t_doom3d *app)
{
	t_3d_object		*object;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	object = place_scene_object(app, (const char*[3]){
		"assets/models/window/window_wall.obj",
		"assets/textures/wall_metal_panel.bmp", NULL}, pos);
	object->material->shading_opts = e_shading_transparent |
		e_shading_uv_repeat;
	placement_notification(app, "Placing window wall!");
	return (object);
}
