/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_place.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:43:49 by veilo             #+#    #+#             */
/*   Updated: 2021/05/04 20:03:11 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Audio trigger
** key_id is used to select what audio log to play
*/

t_3d_object	*place_jukebox(t_doom3d *app)
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
		e_shading_invisible | e_shading_transparent);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	if (app->editor.patrol_slot < AUDIO_LOG)
		trigger_params.key_id = app->editor.patrol_slot;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_jukebox);
	LOG_INFO("Placed jukebox");
	return (trigger);
}

/*
** Music trigger
** key_id is used to select what audio log to play
*/

t_3d_object	*place_musicbox(t_doom3d *app)
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
		e_shading_invisible | e_shading_transparent);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	if (app->editor.patrol_slot < AUDIO_LOG)
		trigger_params.key_id = app->editor.patrol_slot;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_musicbox);
	LOG_INFO("Placed musicbox");
	return (trigger);
}

/*
** Hurtbox trigger
*/

t_3d_object	*place_hurt_box(t_doom3d *app)
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
		e_shading_invisible | e_shading_transparent);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects
	[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_hurtbox);
	LOG_INFO("Placed hurtbox");
	return (trigger);
}

t_3d_object	*place_drop_shotgun(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/shotgun.obj",
			"assets/textures/shotgun_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_weapon_drop_shotgun);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Shotgun placed %d", trigger->id);
	return (trigger);
}

t_3d_object	*place_elevator_switch(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/keypad.obj",
			"assets/textures/keypad_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	trigger_params.key_id = -1;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_elevator_switch);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.5, 0.5, 0.5);
	LOG_INFO("Elevator switch placed %d", trigger->id);
	return (trigger);
}
