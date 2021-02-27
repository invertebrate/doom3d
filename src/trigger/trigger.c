/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:54:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 15:20:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			place_drop_shotgun(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;

	editor_place_position(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	place_scene_object(app,
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
}

void			place_drop_jetpack(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;

	editor_place_position(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	place_scene_object(app,
		(const char*[3]){NPC_DEFAULT_MODEL,
			NPC_DEFAULT_TEXTURE, NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_item_jetpack);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.2, 0.2, 0.2);
}

void			place_elevator_switch(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;

	editor_place_position(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	place_scene_object(app,
		(const char*[3]){NPC_DEFAULT_MODEL,
			ELEVATOR_SWITCH_TEXTURE, NULL}, pos);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_elevator_switch);
	l3d_3d_object_scale(
		app->active_scene->objects[app->active_scene->last_object_index],
		0.5, 0.5, 0.5);
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
			elevator_go_to_next_node(app, trigger->linked_obj[0]);
		}
	}
}

void			trigger_link_object_to_npc(t_3d_object *trigger_obj,
					t_3d_object *target_npc)
{
	t_trigger	*trigger;
	t_npc		*npc;

	npc = target_npc->params;
	trigger = trigger_obj->params;
	if (trigger_obj->params_type != trigger_elevator_switch)
		ft_printf("This trigger cannot be linked\n");
	else if (npc->type == npc_type_elevator)
	{
		if (trigger->linked_obj[0] == target_npc)
		{
			trigger->linked_obj[0] = NULL;
			trigger->num_links--;
			ft_printf("unlinked object\n");
		}
		else
		{
			trigger->linked_obj[0] = target_npc;
			trigger->num_links++;
			ft_printf("linked object!\n");
		}
	}
	else
		ft_printf("This object cannot be linked\n");
}

void			place_player_start(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;

	editor_place_position(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	place_scene_object(app,
		(const char*[3]){"assets/models/box.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_player_start);
}

void			place_player_end(t_doom3d *app)
{
	t_vec3		pos;
	t_trigger	trigger_params;

	editor_place_position(app, pos);
	ft_memset(&trigger_params, 0, sizeof(t_trigger));
	place_scene_object(app,
		(const char*[3]){"assets/models/box.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(
		app->active_scene->objects[app->active_scene->last_object_index],
		e_shading_invisible);
	app->active_scene->objects[app->active_scene->last_object_index]->type =
		object_type_trigger;
	trigger_params.parent = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_3d_object_set_params(
		app->active_scene->objects[app->active_scene->last_object_index],
		&trigger_params, sizeof(t_trigger), trigger_player_end);
}
