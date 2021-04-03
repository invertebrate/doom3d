/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:10:02 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/04 00:40:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_editor_placement_start(t_doom3d *app,
			uint32_t obj_type, void *data)
{
	t_3d_object	*obj;

	app->editor.is_placing = true;
	obj = NULL;
	editor_deselect_all(app);
	if (obj_type == object_type_light)
		obj = editor_place_light_object(app);
	else if (obj_type == object_type_trigger)
		obj = editor_place_trigger_object(app, (t_trigger_type)data);
	else if (obj_type == object_type_default)
		obj = editor_place_default_object(app, data);
	else if (obj_type == object_type_npc)
		obj = editor_place_npc_object(app, (t_npc_type)data);
	if (obj)
	{
		active_scene_update_after_objects(app->active_scene);
		editor_objects_invisible_highlight(app);
		select_object(app, obj);
	}
	else
		app->editor.is_placing = false;
}

void	handle_editor_placement_cancel(t_doom3d *app)
{
	push_custom_event(app, event_editor_delete, NULL, NULL);
	app->editor.is_placing = false;
}

void	handle_editor_placement_end(t_doom3d *app)
{
	app->editor.is_placing = false;
	notify_user(app, (t_notification){
		.message = "Placed!",
		.type = notification_type_info, .time = 2000});
	push_custom_event(app, event_editor_select, NULL, NULL);
}

void	handle_editor_snap_to_grid(t_doom3d *app)
{
	int32_t		i;
	t_3d_object	*selected_obj;
	t_vec3		snap_amount;

	if (app->editor.num_selected_objects == 0)
		return ;
	i = -1;
	while (++i < app->editor.num_selected_objects)
	{
		selected_obj = app->editor.selected_objects[i];
		ml_vector3_sub(selected_obj->position, (t_vec3){
			(int32_t)selected_obj->position[0] / (int32_t)app->unit_size,
			(int32_t)selected_obj->position[1] / (int32_t)app->unit_size,
			(int32_t)selected_obj->position[2] / (int32_t)app->unit_size
		}, snap_amount);
		l3d_3d_object_translate(selected_obj,
			snap_amount[0], snap_amount[1], snap_amount[2]);
	}
}
