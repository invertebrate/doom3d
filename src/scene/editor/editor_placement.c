/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_placement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:50:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 16:04:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

uint32_t		get_light_emit_color(t_3d_object *light_obj)
{
	t_light_type	light_type;

	if (light_obj->type == object_type_light)
	{
		light_type = light_obj->params_type;
		if (light_type == light_type_yellow)
			return (L3D_COLOR_YELLOW);
		else if (light_type == light_type_red)
			return (L3D_COLOR_RED);
		else if (light_type == light_type_green)
			return (L3D_COLOR_GREEN);
		else if (light_type == light_type_blue)
			return (L3D_COLOR_BLUE);
		else if (light_type == light_type_cyan)
			return (L3D_COLOR_CYAN);
		return (L3D_COLOR_YELLOW);
	}
	// Projectile (customize colors based on param->type if you wish)
	else
		return (L3D_COLOR_RED);
}

t_shading_opts	get_light_shading(t_light_type light_type)
{
	if (light_type == light_type_yellow)
		return (e_shading_yellow);
	else if (light_type == light_type_red)
		return (e_shading_red);
	else if (light_type == light_type_green)
		return (e_shading_green);
	else if (light_type == light_type_blue)
		return (e_shading_blue);
	else if (light_type == light_type_cyan)
		return (e_shading_cyan);
	return (e_shading_yellow);		
}

/*
** Place a light object in editor. Light type defines what color is emmitted.
*/

t_3d_object		*editor_place_light_object(t_doom3d *app,
					t_light_type light_type)
{
	t_3d_object		*light;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	light = place_scene_object(app, (const char*[3]){
		"assets/models/light_sphere.obj", NULL,  NULL}, pos);
	l3d_object_set_shading_opts(light,
		e_shading_transparent | get_light_shading(light_type));
	light->type = object_type_light;
	light->params_type = light_type;
	editor_objects_invisible_highlight(app);\
	return (light);
}

static void		placement_notification(t_doom3d *app, char *txt)
{
	notify_user(app, (t_notification){
			.message = txt,
			.type = notification_type_info, .time = 2000});
}

/*
** Place a trigger object in editor
*/

t_3d_object		*editor_place_trigger_object(t_doom3d *app,
					t_trigger_type trigger_type)
{
	t_3d_object		*trigger;
	t_3d_object		*old_trigger;

	trigger = NULL;
	if (trigger_type == trigger_player_start)
	{
		old_trigger =
			find_one_object_by_type(app, object_type_trigger, trigger_player_start);
		if (old_trigger)
		{
			placement_notification(app, "Old Start Trigger found, deleting it!");
			push_custom_event(app, event_object_delete, old_trigger, NULL);
		}
		trigger = place_player_start(app);
		placement_notification(app, "Placing Player Start!");
	}
	else if (trigger_type == trigger_player_end)
	{
		old_trigger =
			find_one_object_by_type(app, object_type_trigger, trigger_player_end);
		if (old_trigger)
		{
			placement_notification(app, "Old End Trigger found, deleting it!");
			push_custom_event(app, event_object_delete, old_trigger, NULL);
		}
		trigger = place_player_end(app);
		placement_notification(app, "Placing Player End!");
	}
	else if (trigger_type == trigger_weapon_drop_shotgun)
	{
		trigger = place_drop_shotgun(app);
		placement_notification(app, "Placing shotgun trigger");
	}
	else if (trigger_type == trigger_weapon_drop_pistol)
	{
		trigger = place_drop_pistol(app);
		placement_notification(app, "Placing pistol trigger");
	}
	else if (trigger_type == trigger_weapon_drop_rpg)
	{
		trigger = place_drop_rpg(app);
		placement_notification(app, "Placing RPG trigger");
	}
	else if (trigger_type == trigger_item_jetpack)
	{
		trigger = place_drop_jetpack(app);
		placement_notification(app, "Placing jetpack trigger");
	}
	else if (trigger_type == trigger_item_medkit)
	{
		trigger = place_drop_medkit(app);
		placement_notification(app, "Placing medkit trigger");
	}
	else if (trigger_type == trigger_item_key)
	{
		trigger = place_drop_key(app);
		placement_notification(app, "Placing key trigger");
	}
	else if (trigger_type == trigger_elevator_switch)
	{
		trigger = place_elevator_switch(app);
		placement_notification(app, "Placing door/elevator switch");
	}
	else if (trigger_type == trigger_door_switch)
	{
		trigger = place_elevator_switch_timer(app);
		placement_notification(app, "Placing door/elevator timer switch");
	}
	return (trigger);
}

/*
** This is ugly, I know. I'm a little ashamed. Normal objects should belong
** somewhere else, but norms & UI space makes it a bit hard so here they are
** filenames get passed as void* in case the data could not be cast to
** any prefab type...
*/

t_3d_object		*editor_place_default_object(t_doom3d *app, void *data)
{
	t_3d_object		*model;
	t_3d_object		*object;
	t_vec3			pos;

	object = NULL;
	if ((t_prefab_type)data == prefab_plane)
	{
		editor_pos_camera_front(app, pos);
		model = l3d_plane_create(NULL, NULL);
		object = place_procedural_scene_object(app, model, (const char*[2]){
			"assets/textures/lava.bmp",
			"assets/textures/lava_normal.bmp"
		}, pos);
		l3d_3d_object_destroy(model);
		placement_notification(app, "Placing plane!");
	}
	else if ((t_prefab_type)data == prefab_path_node)
	{
		object = place_path_object(app);
		placement_notification(app, "Placing Path Node!");
	}
	else if ((char*)data)
	{
		editor_pos_camera_front(app, pos);
		object = place_scene_object(app,
			(const char *[3]){data, NULL, NULL}, pos);
	}
	return (object);
}

/*
** Place an npc object in editor
*/

t_3d_object		*editor_place_npc_object(t_doom3d *app, t_npc_type type)
{
	t_vec3			pos;
	t_3d_object		*object;

	editor_pos_camera_front(app, pos);
	object = npc_spawn(app, pos, 0, type);
	placement_notification(app, "Placing Npc!");
	return (object);
}