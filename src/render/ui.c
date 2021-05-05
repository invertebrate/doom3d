/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 21:09:54 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	render_main_game_ui(t_doom3d *app)
{
	int32_t				height;

	height = app->window->framebuffer->height;
	if (app->player.hp <= 0.2 * app->player.max_hp
		&& !app->active_scene->is_paused)
		framebuffer_health_low_overlay(app);
	render_hud(app);
	if (app->active_scene->is_paused)
	{
		framebuffer_dark_overlay(app->window->framebuffer);
		render_button_menu(app->active_scene->menus[0], (t_vec2){100,
			height / 2 - app->active_scene->menus[0]->buttons[0]->height
			* app->active_scene->menus[0]->num_buttons / 2});
	}
}

static void	render_main_menu_or_settings_menu(t_doom3d *app)
{
	int32_t		height;

	height = app->window->framebuffer->height;
	render_ui_title(app);
	render_button_menu(app->active_scene->menus[0], (t_vec2){100,
		height / 2
		- app->active_scene->menus[0]->buttons[0]->height
		* app->active_scene->menus[0]->num_buttons / 2});
}

/*
** Render UI (Menus, HUD, notifications, etc. depending on scene)
*/

void	render_ui(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_menu
		|| app->active_scene->scene_id == scene_id_main_menu_settings)
		render_main_menu_or_settings_menu(app);
	else if (app->active_scene->scene_id == scene_id_main_game)
		render_main_game_ui(app);
	else if (app->active_scene->scene_id == scene_id_editor3d)
		render_editor_ui(app);
	render_notifications(app,
		(t_vec2){app->window->framebuffer->width - 100, 10});
}
