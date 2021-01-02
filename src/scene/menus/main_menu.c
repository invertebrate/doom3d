/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:51:38 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 17:15:46 by ohakola          ###   ########.fr       */
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
	}
	else if (self->id == 1)
	{
		app->next_scene_id = scene_id_editor3d;
	}
	else if (self->id == 2)
	{
		app->next_scene_id = scene_id_main_menu_settings;
	}
	else if (self->id == 3)
		app->is_running = false;
}

void				main_menu_create(t_doom3d *app)
{
	app->active_scene->menus[0] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[4]){
				"Start Game",
				"Editor",
				"Settings",
				"Quit"},
			.num_buttons = 4,
			.on_click = on_main_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->num_button_menus = 1;
}
