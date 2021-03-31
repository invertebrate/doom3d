/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:10:02 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 23:35:41 by ohakola          ###   ########.fr       */
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
	doom3d_notification_add(app, (t_notification){
		.message = "Placed!",
		.type = notification_type_info, .time = 2000});
}
