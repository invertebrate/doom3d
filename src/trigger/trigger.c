/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:54:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/22 18:41:38 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object		*place_drop_shotgun(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/shotgun.obj",
			"assets/textures/shotgun_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_weapon_drop_shotgun);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Shotgun placed %d", trigger->id);
	return (trigger);
}

t_3d_object		*place_drop_pistol(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/pistol.obj",
			"assets/textures/pistol_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_weapon_drop_pistol);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Pistol placed %d", trigger->id);
	return (trigger);
}

t_3d_object		*place_drop_rpg(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/rpg.obj",
			"assets/textures/rpg_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_weapon_drop_rpg);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.7, 0.7, 0.7);
	LOG_INFO("RPG placed %d", trigger->id);
	return (trigger);
}

t_3d_object		*place_drop_jetpack(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/jetpack.obj",
			"assets/textures/keypad_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_item_jetpack);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Jetpack placed %d", trigger->id);
	return (trigger);
}

t_3d_object		*place_drop_medkit(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/medkit.obj",
			"assets/textures/medkit_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_item_medkit);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
	LOG_INFO("Medkit placed %d", trigger->id);
	return (trigger);
}

t_3d_object		*place_drop_key(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){NPC_DEFAULT_MODEL,
			NPC_DEFAULT_TEXTURE, NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
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

t_3d_object		*place_elevator_switch(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/keypad.obj",
			"assets/textures/keypad_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
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

t_3d_object		*place_elevator_switch_timer(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/keypad.obj",
			"assets/textures/keypad_texture.bmp", NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	trigger_params.key_id = -1;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_elevator_switch_timer);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.5, 0.5, 0.5);
	LOG_INFO("Elevator timer switch placed %d", trigger->id);
	return (trigger);
}

void			trigger_activate(t_doom3d *app, t_3d_object *obj)
{
	t_trigger	*trigger;

	if ((trigger = obj->params) == NULL)
		return ;
	if (obj->params_type == trigger_elevator_switch)
	{
		if (trigger->linked_obj[0])
		{
			if (trigger->key_id == -1 ||
				app->player.keys[trigger->key_id] == true)
			{
				elevator_go_to_next_node(app, trigger->linked_obj[0]);
				push_custom_event(app, event_effect_play,
					(void*)sf_door_open, s_ini(0, 1, st_game, 1.0));
			}
			else
			{
				LOG_INFO("Player is missing key!");
				push_custom_event(app, event_effect_play,
					(void*)sf_door_locked, s_ini(0, 1, st_game, 1.0));
			}
		}
	}
	if (obj->params_type == trigger_elevator_switch_timer)
	{
		if (trigger->linked_obj[0])
		{
			elevator_go_to_next_node(app, trigger->linked_obj[0]);
			push_custom_event(app, event_effect_play,
				(void*)sf_door_open, s_ini(0, 1, st_game, 1.0));
		}
		trigger_timer_start(app, trigger->linked_obj[0]);
	}
}

void			trigger_link_object_to_npc(t_3d_object *trigger_obj,
					t_3d_object *target_npc)
{
	t_trigger	*trigger;
	t_npc		*npc;

	npc = target_npc->params;
	trigger = trigger_obj->params;
	if (trigger_obj->params_type != trigger_elevator_switch &&
		trigger_obj->params_type != trigger_elevator_switch_timer)
		LOG_ERROR("Trigger %d cannot be linked", trigger_obj->id);
	else if (npc->type == npc_type_elevator)
	{
		if (trigger->linked_obj[0] == target_npc)
		{
			trigger->linked_obj[0] = NULL;
			trigger->num_links--;
			LOG_INFO("Unlinked trigger %d", trigger_obj->id);
		}
		else
		{
			trigger->linked_obj[0] = target_npc;
			trigger->num_links++;
			LOG_INFO("Linked trigger %d", trigger_obj->id);
		}
	}
	else
		ft_printf("This object cannot be linked\n");
}

void			trigger_update_key_id(t_doom3d *app, t_3d_object *key)
{
	t_trigger	*trigger;

	if (key->params_type == trigger_item_key ||
		key->params_type == trigger_elevator_switch)
	{
		trigger = key->params;
		if (trigger && key->params_type == trigger_elevator_switch &&
			trigger->key_id == app->editor.patrol_slot)
		{
			trigger->key_id = -1;
			LOG_INFO("Removed key requirement from door/elevator %d", key->id);
		}
		else if (app->editor.patrol_slot < MAX_KEYS)
		{
			trigger->key_id = app->editor.patrol_slot;
			LOG_INFO("Key id set to slot %d", key->id, app->editor.patrol_slot);
		}
	}
}

t_3d_object		*place_player_start(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/box.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible | e_shading_transparent);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_player_start);
	LOG_INFO("Placed player start");
	return (trigger);
}

t_3d_object		*place_player_end(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;
	t_3d_object	*trigger;

	editor_pos_camera_front(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	trigger = place_scene_object(app,
		(const char*[3]){"assets/models/box.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible | e_shading_transparent);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_player_end);
	LOG_INFO("Placed player end");
	return (trigger);
}
