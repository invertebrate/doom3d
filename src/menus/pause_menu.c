/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:02:10 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:51:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	on_pause_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
		push_custom_event(app, event_scene_change,
			(void *)scene_id_main_menu, NULL);
	else if (self->id == 1)
		push_custom_event(app, event_quit, NULL, NULL);
}

/*
** Create pause menu
*/

void	pause_menu_create(t_doom3d *app)
{
	error_check(!(app->active_scene->menus
			= ft_calloc(sizeof(t_button_group*) * 1)),
		"Failed to malloc menus");
	app->active_scene->menus[0] = button_menu_create(app,
			(t_button_menu_params){
			.button_names = (const char*[4]){
			"Main Menu",
			"Quit"},
			.num_buttons = 2,
			.on_click = on_pause_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->num_button_menus = 1;
}
