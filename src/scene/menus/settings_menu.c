/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:41:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/18 17:19:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_settings_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
	{
		app->settings.width = 960;
		app->settings.height = 540;
		window_resize(app->window, app->settings.width, app->settings.height);
	}
	else if (self->id == 1)
	{
		app->settings.width = 1280;
		app->settings.height = 720;
		window_resize(app->window, app->settings.width, app->settings.height);
	}
	else if (self->id == 2)
	{
		app->settings.width = 1920;
		app->settings.height = 1080;
		window_resize(app->window, app->settings.width, app->settings.height);
	}
	else if (self->id == 3)
	{
		app->next_scene_id = scene_id_main_menu;
	}
}

void				settings_menu_create(t_doom3d *app)
{
	error_check(!(app->active_scene->menus =
		ft_calloc(sizeof(t_button_group*) * 1)), "Failed to malloc menus");
	app->active_scene->menus[0] = button_menu_create(app,
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
