/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:51:38 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/22 23:33:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_main_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
	{
		app->next_scene_id = scene_id_main_game;
		scene_next_select(app);
	}
	else if (self->id == 1)
	{
		app->next_scene_id = scene_id_editor3d;
		scene_next_select(app);
	}
	else if (self->id == 2)
	{
		app->next_scene_id = scene_id_main_menu_settings;
		scene_next_select(app);
	}
	else if (self->id == 3)
		app->is_running = false;
}

void				main_menu_create(t_doom3d *app)
{
	app->active_scene->menus[0] = button_menu_create(app, (const char*[4]){
		"Start Game",
		"Editor",
		"Settings",
		"Quit"}, 4, on_main_menu_button_click);
	app->active_scene->num_menus = 1;
}
