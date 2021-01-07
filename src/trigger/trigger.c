/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:54:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/07 14:27:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			place_player_start(t_doom3d *app)
{
	t_3d_object		*model;
	t_trigger		trigger;

	model = l3d_plane_create(NULL, NULL);
	place_procedural_scene_object(app, model,
		(const char*[2]){"assets/models/box.obj", NULL},
		(t_vec3){0, 0, 0});
	l3d_3d_object_destroy(model);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->num_objects - 1],
		e_shading_invisible);
	ft_memcpy(&trigger.aabb,
		&app->active_scene->objects[app->active_scene->num_objects - 1]->aabb,
		sizeof(t_box3d));
	trigger.id = trigger_player_start;
	trigger.type = trigger_player_start;
	app->active_scene->objects[app->active_scene->num_objects - 1]->type =
		object_type_trigger;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->num_objects - 1],
		&trigger, sizeof(t_trigger), trigger_player_start);
}

void			place_player_end(t_doom3d *app)
{
	t_3d_object		*model;
	t_trigger		trigger;

	model = l3d_plane_create(NULL, NULL);
	place_procedural_scene_object(app, model,
		(const char*[2]){"assets/models/box.obj", NULL},
		(t_vec3){0, 0, 0});
	l3d_3d_object_destroy(model);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->num_objects - 1],
		e_shading_invisible);
	ft_memcpy(&trigger.aabb,
		&app->active_scene->objects[app->active_scene->num_objects - 1]->aabb,
		sizeof(t_box3d));
	trigger.id = trigger_player_start;
	trigger.type = trigger_player_start;
	app->active_scene->objects[app->active_scene->num_objects - 1]->type =
		object_type_trigger;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->num_objects - 1],
		&trigger, sizeof(t_trigger), trigger_player_end);
}

void			editor_triggers_highlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj)
		{
			if (obj->type == object_type_trigger)
			{
				obj->material->shading_opts = (obj->material->shading_opts &
					~(e_shading_invisible));
				obj->material->shading_opts = e_shading_blue;
				if (obj->params_type == place_player_start)
					obj->material->shading_opts = e_shading_green;
				if (obj->params_type == place_player_end)
					obj->material->shading_opts = e_shading_red;
			}
		}
	}
}

void			editor_triggers_unhighlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj && obj->type == object_type_trigger)
			obj->material->shading_opts = e_shading_invisible;
	}
}