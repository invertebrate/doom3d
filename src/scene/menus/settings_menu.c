/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:41:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 20:19:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_settings_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
		push_custom_event(app, event_window_resize, (void*)960, (void*)540);
	else if (self->id == 1)
		push_custom_event(app, event_window_resize, (void*)1280, (void*)720);
	else if (self->id == 2)
		push_custom_event(app, event_window_resize, (void*)1920, (void*)1080);
	else if (self->id == 3)
		push_custom_event(app, event_scene_change,
			(void*)scene_id_main_menu, NULL);
}

/*
** Create settings menu
*/
void				settings_menu_create(t_doom3d *app)
{
	error_check(!(app->active_scene->menus =
		ft_calloc(sizeof(t_button_group*) * 1)), "Failed to malloc menus");
	app->active_scene->menus[0] = button_menu_create_shaded(app,
		(t_button_menu_params){
			.button_names = (const char*[4]){
				"Small",
				"Medium",
				"Large",
				"Back"},
			.num_buttons = 4,
			.on_click = on_settings_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->num_button_menus = 1;
}
