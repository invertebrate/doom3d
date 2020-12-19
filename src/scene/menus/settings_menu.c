/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:41:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/18 19:23:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_settings_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
		window_resize(app->window, 960, 540);
	else if (self->id == 1)
		window_resize(app->window, 1280, 720);
	else if (self->id == 2)
		window_resize(app->window, 1920, 1080);
	else if (self->id == 3)
	{
		app->next_scene_id = scene_id_main_menu;
		scene_next_select(app);
	}
}

void				settings_menu_create(t_doom3d *app)
{
	app->active_scene->menus[0] = button_menu_create(app, (const char*[4]){
		"Small\0",
		"Medium\0",
		"Large\0",
		"Back\0"}, 4, on_settings_menu_button_click);
	app->active_scene->num_menus = 1;
}
