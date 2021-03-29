/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:43:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 17:43:31 by ohakola          ###   ########.fr       */
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