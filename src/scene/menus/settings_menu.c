/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:41:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/16 16:54:28 by ohakola          ###   ########.fr       */
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
	const char	*options[4];

	options[0] = "960x540";
	options[1] = "1280x720";
	options[2] = "1920x1080";
	options[3] = "Back";
	app->active_scene->menu = button_menu_create(app, options, 4,
		on_settings_menu_button_click);
}
