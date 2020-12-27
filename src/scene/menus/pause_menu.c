/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:02:10 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/26 13:22:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_pause_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
	{
		app->next_scene_id = scene_id_main_menu;
	}
	else if (self->id == 1)
	{
		app->is_running = false;
	}
}

void				pause_menu_create(t_doom3d *app)
{
	app->active_scene->menus[0] = button_menu_create(app, (const char*[4]){
		"Main Menu",
		"Quit"}, 2, on_pause_menu_button_click);
	app->active_scene->num_menus = 1;
}
