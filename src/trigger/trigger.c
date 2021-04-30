/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:54:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/30 22:14:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

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
	trigger_params.parent = app->active_scene->objects[app->active_scene->
														last_object_index];
	trigger_params.key_id = -1;
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_door_switch);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.5, 0.5, 0.5);
	LOG_INFO("Elevator timer switch placed %d", trigger->id);
	return (trigger);
}

void			trigger_activate(t_doom3d *app, t_3d_object *obj)
{
	t_trigger	*trigger;

	trigger = NULL;
	if ((trigger = obj->params) == NULL)
		return ;
	if (obj->params_type == trigger_elevator_switch)
	{
		trigger_handle_elevator_switch(app, trigger);
	}
	if (obj->params_type == trigger_door_switch)
	{
		trigger_handle_door_switch(app, trigger);
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
		trigger_obj->params_type != trigger_door_switch)
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

	trigger = NULL;
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
			LOG_INFO("Key id %d set to slot %d", key->id,
						app->editor.patrol_slot);
		}
	}
	else if (key->params_type == trigger_jukebox)
		trigger_handle_trigger_jukebox(app, key, NULL);
}

void			get_trigger_action_text(t_trigger_type type,
					char *action_text)
{
	if (type == trigger_weapon_drop_shotgun)
		ft_sprintf(action_text, "Walk over to pick up Shotgun ammo");
	else if (type == trigger_weapon_drop_pistol)
		ft_sprintf(action_text, "Walk over to pick up Pistol ammo");
	else if (type == trigger_weapon_drop_rpg)
		ft_sprintf(action_text, "Walk over to pick up RPG ammo");
	else if (type == trigger_item_medkit)
		ft_sprintf(action_text, "Walk over to pick up Medkit");
	else if (type == trigger_item_key)
		ft_sprintf(action_text, "Walk over to pick up Key");
	else if (type == trigger_item_jetpack)
		ft_sprintf(action_text, "Walk over to pick up Jetpack");
	else if (type == trigger_elevator_switch)
		ft_sprintf(action_text, "Press E to use elevator");
	else if (type == trigger_door_switch)
		ft_sprintf(action_text, "Press E to use door");
	else
		action_text[0] = '\0';
}
