/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 15:51:38 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 17:08:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_main_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
		doom3d_push_event(app, event_scene_change,
			(void*)scene_id_main_game, NULL);
	else if (self->id == 1)
		doom3d_push_event(app, event_scene_change,
			(void*)scene_id_editor3d, NULL);
	else if (self->id == 2)
		doom3d_push_event(app, event_scene_change,
			(void*)scene_id_main_menu_settings, NULL);
	else if (self->id == 3)
		doom3d_push_event(app, event_quit, NULL, NULL);
}

void				main_menu_create(t_doom3d *app)
{
	error_check(!(app->active_scene->menus =
		ft_calloc(sizeof(t_button_group*) * 1)), "Failed to malloc menus");
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
