/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu_button_clicks1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/12 10:54:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	on_editor_menu_button_click(t_button *self, void *params)
{
	t_editor_menu_index	new_menu_id;

	new_menu_id = editor_menu_none;
	if (self->id == 0)
		on_editor_exit_button_click(params);
	else if (self->id == 1)
		on_editor_save_button_click(params);
	else if (self->id == 2)
		new_menu_id = editor_menu_objects;
	else if (self->id == 3)
		new_menu_id = editor_menu_textures;
	else if (self->id == 4)
		new_menu_id = editor_menu_normalmaps;
	else if (self->id == 5)
		new_menu_id = editor_menu_prefabs;
	else if (self->id == 6)
		new_menu_id = editor_menu_npcs;
	else if (self->id == 7)
		new_menu_id = editor_menu_triggers;
	else if (self->id == 8)
		new_menu_id = editor_menu_lights;
	if (self->id > 1 && !((t_doom3d *)params)->editor.is_saving)
		push_custom_event(params, event_editor_open_popup_menu,
			(void *)new_menu_id, (void *)self->pos);
}

void	on_new_level_menu_button_click(t_button *self, void *params)
{
	t_doom3d			*app;

	app = params;
	if (self->id == 0 && app->editor.editor_level < MAX_LEVELS)
	{
		if (!app->level_list[app->editor.editor_level])
		{
			notify_user(app, (t_notification){
				.message
				= "Save map first, and add it to assets/level_list.txt!!",
				.type = notification_type_info, .time = 2000});
			return ;
		}
		editor_init(app, app->editor.editor_level
			+ app->num_levels - app->editor.editor_level);
		app->editor.is_new_map = true;
		push_custom_event(app, event_scene_reload, NULL, NULL);
	}
	else if (self->id == 0 && app->editor.editor_level == MAX_LEVELS)
		notify_user(app, (t_notification){
			.message = "Too many levels created!!",
			.type = notification_type_info, .time = 2000});
}

void	on_guide_menu_button_click(t_button *self, void *params)
{
	push_custom_event(params, event_editor_open_popup_menu,
		(void *)editor_menu_guide, (void *)self->pos);
}
