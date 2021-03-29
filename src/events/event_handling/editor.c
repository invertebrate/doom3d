/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:43:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 18:44:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_editor_placement_start(t_doom3d *app)
{
	app->editor.is_placing = true;
}

void	handle_editor_placement_end(t_doom3d *app)
{
	app->editor.is_placing = false;
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
	doom3d_push_event(app, event_scene_change, (void*)scene_id_main_menu, NULL);
	editor_deselect_all(app);
	SDL_StopTextInput();
	app->editor.is_saving = false;
}

void	handle_editor_select(t_doom3d *app)
{
	if (app->mouse.x > app->window->editor_pos[0] && app->mouse.x <
			app->window->editor_pos[0] +
			app->window->editor_framebuffer->width &&
		app->mouse.y > app->window->editor_pos[1] && app->mouse.y <
			app->window->editor_pos[1] +
			app->window->editor_framebuffer->height)
		editor_select(app);
}

void	handle_editor_deselect(t_doom3d *app)
{
	editor_deselect(app);	
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