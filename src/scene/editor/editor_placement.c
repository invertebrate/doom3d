/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_placement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:50:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/30 18:27:16 by ohakola          ###   ########.fr       */
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


t_3d_object		*editor_place_trigger_object(t_doom3d *app,
					t_trigger_type trigger_type)
{
	t_3d_object		*trigger;

	trigger = NULL;
	if (trigger_type == trigger_player_start)
	{
		if (find_one_object_by_type(app, object_type_trigger, trigger_player_start))
			doom3d_notification_add(app, (t_notification){
			.message = "Player Start exists, delete it first!",
			.type = notification_type_info, .time = 2000});
		else
		{
			trigger = place_player_start(app);
			doom3d_notification_add(app, (t_notification){
			.message = "Placing Player Start!",
			.type = notification_type_info, .time = 2000});
			active_scene_update_after_objects(app->active_scene);
			app->editor.is_saved = false;
		}
	}
	else if (trigger_type == trigger_player_end)
	{
		if (find_one_object_by_type(app, object_type_trigger, trigger_player_end))
			doom3d_notification_add(app, (t_notification){
			.message = "Player End exists, delete it first!",
			.type = notification_type_info, .time = 2000});
		else
		{
			trigger = place_player_end(app);
			doom3d_notification_add(app, (t_notification){
			.message = "Placing Player End!",
			.type = notification_type_info, .time = 2000});
			active_scene_update_after_objects(app->active_scene);
			app->editor.is_saved = false;
		}
	}
	else if (trigger_type == trigger_weapon_drop_shotgun)
	{
		trigger = place_drop_shotgun(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placing shotgun trigger",
			.type = notification_type_info, .time = 2000});
		active_scene_update_after_objects(app->active_scene);
		app->editor.is_saved = false;
	}
	else if (trigger_type == trigger_item_jetpack)
	{
		trigger = place_drop_jetpack(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placing jetpack trigger",
			.type = notification_type_info, .time = 2000});
		active_scene_update_after_objects(app->active_scene);
		app->editor.is_saved = false;
	}
	else if (trigger_type == trigger_item_key)
	{
		trigger = place_drop_key(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placing key trigger",
			.type = notification_type_info, .time = 2000});
		active_scene_update_after_objects(app->active_scene);
		app->editor.is_saved = false;
	}
	else if (trigger_type == trigger_elevator_switch)
	{
		trigger = place_elevator_switch(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placing door/elevator switch",
			.type = notification_type_info, .time = 2000});
		active_scene_update_after_objects(app->active_scene);
		app->editor.is_saved = false;
	}
	editor_objects_invisible_highlight(app);
	return (trigger);
}