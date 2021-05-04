/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_place2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:39:02 by veilo             #+#    #+#             */
/*   Updated: 2021/05/04 20:00:48 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object	*place_drop_pistol(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/pistol.obj",
			"assets/textures/pistol_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_weapon_drop_pistol);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Pistol placed %d", trigger->id);
	return (trigger);
}

t_3d_object	*place_drop_rpg(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/rpg.obj",
			"assets/textures/rpg_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_weapon_drop_rpg);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.7, 0.7, 0.7);
	LOG_INFO("RPG placed %d", trigger->id);
	return (trigger);
}

t_3d_object	*place_drop_jetpack(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/jetpack.obj",
			"assets/textures/keypad_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_item_jetpack);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Jetpack placed %d", trigger->id);
	return (trigger);
}

t_3d_object	*place_drop_medkit(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/medkit.obj",
			"assets/textures/medkit_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_item_medkit);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Medkit placed %d", trigger->id);
	return (trigger);
}

t_3d_object	*place_drop_key(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
			(const char *[3]){"assets/models/keycard.obj",
			"assets/textures/keypad_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type
		= object_type_trigger;
	trigger_params.parent = app->active_scene->objects[
		app->active_scene->last_object_index];
	if (app->editor.patrol_slot < MAX_KEYS)
		trigger_params.key_id = app->editor.patrol_slot;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_item_key);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Key placed %d", trigger->id);
	return (trigger);
}
