/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:54:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/15 16:08:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			place_drop_shotgun(t_doom3d *app)
{
	place_scene_object(app,
		(const char*[3]){"assets/models/shotgun.obj",
			"assets/textures/shotgun_texture.bmp", NULL},
		(t_vec3){0, 0, 0});
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		NULL, 0, trigger_weapon_drop_shotgun);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
}

void			place_player_start(t_doom3d *app)
{
	place_scene_object(app,
		(const char*[3]){"assets/models/box.obj", NULL, NULL},
		(t_vec3){0, 0, 0});
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		NULL, 0, trigger_player_start);
}

void			place_player_end(t_doom3d *app)
{
	place_scene_object(app,
		(const char*[3]){"assets/models/box.obj", NULL, NULL},
		(t_vec3){0, 0, 0});
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		NULL, 0, trigger_player_end);
}

void			editor_objects_invisible_highlight(t_doom3d *app)
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
			if (obj->type == object_type_trigger ||
				obj->type == object_type_light)
			{
				obj->material->shading_opts = (obj->material->shading_opts &
					~(e_shading_invisible));
				if (obj->params_type == trigger_player_start)
					obj->material->shading_opts = e_shading_green;
				if (obj->params_type == trigger_player_end)
					obj->material->shading_opts = e_shading_red;
				if (obj->params_type == object_type_light)
					obj->material->shading_opts = e_shading_yellow;
			}
		}
	}
}

void			editor_objects_invisible_unhighlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj &&
			((obj->type == object_type_trigger &&
				(obj->params_type == trigger_player_start ||
					obj->params_type == trigger_player_end)) ||
			obj->type == object_type_light))
			obj->material->shading_opts = e_shading_invisible;
	}
}