/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu_button_clicks2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 03:17:36 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 23:35:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			on_delete_menu_button_click(t_button *self, void *params)
{
	(void)self;
	push_custom_event(params, event_editor_delete, NULL, NULL);
}

void			on_editor_save_button_click(t_doom3d *app)
{
	push_custom_event(app, event_editor_start_save, NULL, NULL);
}

void			on_editor_exit_button_click(t_doom3d *app)
{
	push_custom_event(app, event_editor_exit, NULL, NULL);
}

void			on_objects_menu_button_click(t_button *self, void *params)
{
	push_custom_event(params, event_editor_start_placement,
		(void*)object_type_default, (void*)self->text);
}

void			on_textures_menu_button_click(t_button *self, void *params)
{
	push_custom_event(params, event_editor_add_texture,
		(void*)self->text, NULL);
}
