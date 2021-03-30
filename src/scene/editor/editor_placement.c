/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_placement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:50:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 00:00:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object		*editor_place_light_object(t_doom3d *app)
{
	t_3d_object		*light;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	light = place_scene_object(app, (const char*[3]){
		"assets/models/box.obj", NULL,  NULL}, pos);
	l3d_object_set_shading_opts(light, e_shading_invisible);
	light->type = object_type_light;
	light->params_type = object_type_light;
	editor_objects_invisible_highlight(app);\
	return (light);
}

static void		trigger_notification(t_doom3d *app, char *txt)
{
	doom3d_notification_add(app, (t_notification){
			.message = txt,
			.type = notification_type_info, .time = 2000});
}

t_3d_object		*editor_place_trigger_object(t_doom3d *app,
					t_trigger_type trigger_type)
{
	t_3d_object		*trigger;

	trigger = NULL;
	if (trigger_type == trigger_player_start &&
		find_one_object_by_type(app, object_type_trigger, trigger_player_start))
		trigger_notification(app, "Player Start exists, delete it first!");
	else if (trigger_type == trigger_player_start)
	{
		trigger = place_player_start(app);
		trigger_notification(app, "Placing Player Start!");
	}
	else if (trigger_type == trigger_player_end &&
		find_one_object_by_type(app, object_type_trigger, trigger_player_end))
		trigger_notification(app, "Player End exists, delete it first!");
	else if (trigger_type == trigger_player_end)
	{
		trigger = place_player_end(app);
		trigger_notification(app, "Placing Player End!");
	}
	else if (trigger_type == trigger_weapon_drop_shotgun)
	{
		trigger = place_drop_shotgun(app);
		trigger_notification(app, "Placing shotgun trigger");
	}
	else if (trigger_type == trigger_item_jetpack)
	{
		trigger = place_drop_jetpack(app);
		trigger_notification(app, "Placing jetpack trigger");
	}
	else if (trigger_type == trigger_item_key)
	{
		trigger = place_drop_key(app);
		trigger_notification(app, "Placing key trigger");
	}
	else if (trigger_type == trigger_elevator_switch)
	{
		trigger = place_elevator_switch(app);
		trigger_notification(app, "Placing door/elevator switch");
	}
	return (trigger);
}