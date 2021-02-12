/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:54:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/11 10:01:15 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			place_drop_shotgun(t_doom3d *app)
{
	t_vec3	pos;

	editor_place_position(app, pos);
	place_scene_object(app,
		(const char*[3]){"assets/models/shotgun.obj",
			"assets/textures/shotgun_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		NULL, 0, trigger_weapon_drop_shotgun);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
}

void			place_drop_jetpack(t_doom3d *app)
{
	t_vec3	pos;

	editor_place_position(app, pos);
	place_scene_object(app,
		(const char*[3]){NPC_DEFAULT_MODEL,
			NPC_DEFAULT_TEXTURE, NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		NULL, 0, trigger_item_jetpack);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
}

void			place_player_start(t_doom3d *app)
{
	t_vec3	pos;

	editor_place_position(app, pos);
	place_scene_object(app,
		(const char*[3]){"assets/models/box.obj", NULL, NULL}, pos);
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
	t_vec3	pos;

	editor_place_position(app, pos);
	place_scene_object(app,
		(const char*[3]){"assets/models/box.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		NULL, 0, trigger_player_end);
}
