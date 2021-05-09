/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_place_start_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 22:01:33 by veilo             #+#    #+#             */
/*   Updated: 2021/05/07 12:40:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object	*place_player_start(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/box.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible | e_shading_transparent | e_shading_light);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_player_start);
	LOG_INFO("Placed player start");
	return (trigger);
}

t_3d_object	*place_player_end(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/box.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible | e_shading_transparent | e_shading_light);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_player_end);
	LOG_INFO("Placed player end");
	return (trigger);
}
