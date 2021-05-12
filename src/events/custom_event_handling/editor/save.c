/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:10:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/12 10:49:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Begins saving in editor (starts text input)
*/

void	handle_editor_save_start(t_doom3d *app)
{
	if (!app->editor.is_saving)
	{
		disable_editor_menus_on_save(app);
		editor_deselect_all(app);
		app->editor.is_saving = true;
		SDL_StartTextInput();
		notify_user(app, (t_notification){
			.message = "Write name to save",
			.type = notification_type_info, .time = 2000});
	}
	else
	{
		notify_user(app, (t_notification){
			.message = "Press enter to save",
			.type = notification_type_info, .time = 2000});
	}
}

static void	save_and_handle_highlights(t_doom3d *app)
{
	editor_objects_invisible_unhighlight(app);
	editor_objects_non_culled_unhighlight(app);
	save_map(app);
	editor_objects_invisible_highlight(app);
	editor_objects_non_culled_highlight(app);
}

/*
** Ends saving in editor (stops text input & saves)
*/

void	handle_editor_save_end(t_doom3d *app)
{
	if (!find_one_object_by_type(app, object_type_trigger,
			trigger_player_start)
		|| !find_one_object_by_type(app, object_type_trigger,
			trigger_player_end))
	{
		notify_user(app, (t_notification){
			.message = "You need to add start and end before saving!",
			.type = notification_type_info, .time = 2000});
		return ;
	}
	else if (ft_strlen(app->editor.editor_savename) == 0)
	{
		notify_user(app, (t_notification){.message = "Name must not be empty",
			.type = notification_type_info, .time = 2000});
		return ;
	}
	enable_editor_menus_after_save(app);
	SDL_StopTextInput();
	app->editor.is_saving = false;
	ft_strcpy(app->editor.editor_filename, app->editor.editor_savename);
	save_and_handle_highlights(app);
	notify_user(app, (t_notification){.message = "Saved level!",
		.type = notification_type_info, .time = 2000});
	app->editor.is_saved = true;
}

/*
** Updates filename during save
*/

void	handle_editor_save_type(t_doom3d *app, char *text)
{
	app->editor.is_saved = false;
	ft_strcat(app->editor.editor_savename, text);
	ft_strdel(&text);
}

/*
** Updates filename upon backspace
*/

void	handle_editor_save_type_backspace(t_doom3d *app)
{
	int32_t		length;

	app->editor.is_saved = false;
	length = ft_strlen(app->editor.editor_savename);
	if (length > 0)
		app->editor.editor_savename[length - 1] = '\0';
}
