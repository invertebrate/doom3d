/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/26 13:22:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_save(t_doom3d *app)
{
	if (!app->is_saving)
	{
		app->is_saving = true;
		SDL_StartTextInput();
	}
}

static void			on_editor_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
	{
		app->next_scene_id = scene_id_main_menu;
	}
	if (self->id == 1)
	{
		app->next_scene_id = scene_id_editor2d;
	}
	if (self->id == 2)
		on_save(app);
}

void				editor3d_menu_create(t_doom3d *app)
{
	app->active_scene->menus[0] = button_menu_create(app, (const char*[3]){
		"Exit",
		"2D-Editor",
		"Save"}, 3, on_editor_menu_button_click);
	app->active_scene->num_menus = 1;
}

