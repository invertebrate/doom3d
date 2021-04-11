/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:11:50 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 23:55:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Delete all selected objects
*/

void	handle_editor_delete(t_doom3d *app)
{
	t_3d_object			*object_to_delete;
	int32_t				i;

	if (app->editor.num_selected_objects > 0)
	{
		i = -1;
		while (++i < app->editor.num_selected_objects)
		{
			if (app->editor.selected_objects[i]->type == object_type_path)
				delete_path_object_connections(
					app->editor.selected_objects[i]->params);
			object_to_delete = app->editor.selected_objects[i];
			push_custom_event(app, event_object_delete,
				object_to_delete, NULL);
		}
		app->editor.is_saved = false;
		editor_deselect_all(app);
		notify_user(app, (t_notification){
		.message = "Deleted!",
		.type = notification_type_info, .time = 2000});
	}
}

void	handle_editor_exit(t_doom3d *app)
{
	if (app->editor.is_saving)
	{
		notify_user(app, (t_notification){
			.message = "Save first by pressing enter!",
			.type = notification_type_info, .time = 2000});
		return ;
	}
	if (app->editor.is_placing)
		push_custom_event(app, event_editor_cancel_placement, NULL, NULL);
	push_custom_event(app, event_scene_change, (void*)scene_id_main_menu, NULL);
	editor_deselect_all(app);
	SDL_StopTextInput();
	app->editor.is_saving = false;
}

void	handle_editor_level_switch(t_doom3d *app)
{
	if (app->keyboard.state[SDL_SCANCODE_LCTRL])
		app->editor.editor_level--;
	else
		app->editor.editor_level++;
	if (app->editor.editor_level >= (int32_t)app->num_levels)
		app->editor.editor_level = 0;
	else if (app->editor.editor_level < 0)
		app->editor.editor_level = (int32_t)app->num_levels - 1;
	editor_init(app, app->editor.editor_level);
	push_custom_event(app, event_scene_reload, NULL, NULL);
}

void	handle_editor_open_popup_menu(t_doom3d *app,
			t_editor_menu_index menu_id, t_vec2 pos)
{
	if (app->editor.editor_menu_id != menu_id)
	{
		if (app->editor.editor_menu != NULL)
			button_popup_menu_destroy(app->editor.editor_menu);
		editor_popup_menu_create(app, menu_id, pos);
	}
	app->editor.editor_menu->is_open = true;
	app->editor.editor_menu_id = menu_id;
}
