/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:43:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 00:26:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_editor_placement_start(t_doom3d *app,
			uint32_t obj_type, uint32_t param_type)
{
	t_3d_object	*obj;
	app->editor.is_placing = true;
	obj = NULL;
	editor_deselect_all(app);
	if (obj_type == object_type_light)
		obj = editor_place_light_object(app);
	else if (obj_type == object_type_trigger)
		obj = editor_place_trigger_object(app, param_type);
	else if (obj_type == object_type_default)
		obj = editor_place_prefab_object(app, param_type);
	else if (obj_type == object_type_npc)
		obj = editor_place_npc_object(app, param_type);
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
	doom3d_push_event(app, event_editor_delete, NULL, NULL);
	app->editor.is_placing = false;
}

void	handle_editor_placement_end(t_doom3d *app)
{
	app->editor.is_placing = false;
	doom3d_notification_add(app, (t_notification){
		.message = "Placed!",
		.type = notification_type_info, .time = 2000});
}

void	handle_editor_save_start(t_doom3d *app)
{
	if (!app->editor.is_saving)
	{
		editor_deselect_all(app);
		app->editor.is_saving = true;
		SDL_StartTextInput();
		doom3d_notification_add(app, (t_notification){
			.message = "Write name to save",
			.type = notification_type_info, .time = 2000});
	}
	else
	{
		doom3d_notification_add(app, (t_notification){
			.message = "Press enter to save",
			.type = notification_type_info, .time = 2000});
	}
}

void	handle_editor_save_end(t_doom3d *app)
{
	SDL_StopTextInput();
	app->editor.is_saving = false;
	if (!find_one_object_by_type(app, object_type_trigger,
		trigger_player_start) ||
		!find_one_object_by_type(app, object_type_trigger,
		trigger_player_end))
	{
		doom3d_notification_add(app, (t_notification){
		.message = "You need to add start and end before savind!",
		.type = notification_type_info, .time = 2000});
		return ;
	}
	ft_memcpy(app->editor.editor_filename, app->editor.editor_savename,
		ft_strlen(app->editor.editor_savename));
	editor_objects_invisible_unhighlight(app);
	save_map(app);
	editor_objects_invisible_highlight(app);
	doom3d_notification_add(app, (t_notification){
		.message = "Saved level!",
		.type = notification_type_info, .time = 2000});
	app->editor.is_saved = true;
}

void	handle_editor_save_type(t_doom3d *app, char *text)
{
	app->editor.is_saved = false;
	ft_strcat(app->editor.editor_savename, text);
}

void	handle_editor_save_type_backspace(t_doom3d *app)
{
	int32_t		length;

	app->editor.is_saved = false;
	length = ft_strlen(app->editor.editor_savename);
	if (length > 0)
		app->editor.editor_savename[length - 1] = '\0';
}

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
			doom3d_push_event(app, event_object_delete,
				object_to_delete, NULL);
		}
		app->editor.is_saved = false;
		editor_deselect_all(app);
		doom3d_notification_add(app, (t_notification){
		.message = "Deleted!",
		.type = notification_type_info, .time = 2000});
	}
}

void	handle_editor_exit(t_doom3d *app)
{
	if (app->editor.is_saving)
	{
		doom3d_notification_add(app, (t_notification){
			.message = "Save first by pressing enter!",
			.type = notification_type_info, .time = 2000});
		return ;
	}
	if (app->editor.is_placing)
		doom3d_push_event(app, event_editor_cancel_placement, NULL, NULL);
	doom3d_push_event(app, event_scene_change, (void*)scene_id_main_menu, NULL);
	editor_deselect_all(app);
	SDL_StopTextInput();
	app->editor.is_saving = false;
}

void	handle_editor_select(t_doom3d *app)
{
	if (mouse_inside_editor_view(app))
		editor_select_by_mouse(app);
	if (app->editor.num_selected_objects == 0)
		app->active_scene->menus[1]->is_active = false;
	else
		app->active_scene->menus[1]->is_active = true;
}

void	handle_editor_deselect(t_doom3d *app)
{
	editor_deselect(app);
	if (app->editor.num_selected_objects == 0)
		app->active_scene->menus[1]->is_active = false;	
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
	doom3d_push_event(app, event_scene_reload, NULL, NULL);
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