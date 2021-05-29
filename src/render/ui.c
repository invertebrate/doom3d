/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 20:08:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	render_main_game_ui(t_doom3d *app)
{
	int32_t				height;

	height = app->window->framebuffer->height;
	render_hud(app);
	if (app->player.hp <= 0.2 * app->player.max_hp
		&& !app->active_scene->is_paused)
		framebuffer_health_low_overlay(app);
	if (app->active_scene->is_paused)
	{
		framebuffer_dark_overlay(app->window->framebuffer);
		render_button_menu(app->active_scene->menus[0], (t_vec2){100,
			height / 2 - app->active_scene->menus[0]->buttons[0]->height
			* app->active_scene->menus[0]->num_buttons / 2});
	}
}

static void	set_settings_menu_positions(t_doom3d *app,
				t_vec2 pos1, t_vec2 pos2, t_vec2 pos3)
{
	int32_t		height;

	height = app->window->framebuffer->height;
	ml_vector3_copy((t_vec2){100, height / 2
		- app->active_scene->menus[0]->buttons[0]->height
		* app->active_scene->menus[0]->num_buttons / 2 + 30}, pos1);
	ml_vector3_copy((t_vec2){250, height / 2
		- app->active_scene->menus[0]->buttons[0]->height
		* app->active_scene->menus[0]->num_buttons / 2 + 30}, pos2);
	ml_vector3_copy((t_vec2){400, height / 2
		- app->active_scene->menus[0]->buttons[0]->height
		* app->active_scene->menus[0]->num_buttons / 2 + 30}, pos3);
}

static void	render_settings_menu(t_doom3d *app)
{
	t_vec2		pos1;
	t_vec2		pos2;
	t_vec2		pos3;

	set_settings_menu_positions(app, pos1, pos2, pos3);
	window_text_render_shaded(app->window, (t_text_params){
		.text = "Editor Size", .blend_ratio = 1.0,
		.xy = (int32_t [2]){pos1[0], pos1[1] - 50},
		.text_color = (SDL_Color){255, 0, 0, 255}}, app->window->main_font);
	render_button_menu(app->active_scene->menus[0], pos1);
	window_text_render_shaded(app->window, (t_text_params){
		.text = "Difficulty", .blend_ratio = 1.0,
		.xy = (int32_t [2]){pos2[0], pos2[1] - 50},
		.text_color = (SDL_Color){255, 0, 0, 255}}, app->window->main_font);
	render_button_menu(app->active_scene->menus[1], pos2);
	window_text_render_shaded(app->window, (t_text_params){
		.text = "Select Level", .blend_ratio = 1.0,
		.xy = (int32_t [2]){pos3[0], pos3[1] - 50},
		.text_color = (SDL_Color){255, 0, 0, 255}}, app->window->main_font);
	render_button_menu(app->active_scene->menus[2], pos3);
}

static void	render_main_menu_or_settings_menu(t_doom3d *app)
{
	int32_t		height;

	height = app->window->framebuffer->height;
	render_ui_title(app);
	if (app->active_scene->scene_id == scene_id_main_menu_settings)
		render_settings_menu(app);
	else
	{
		render_button_menu(app->active_scene->menus[0], (t_vec2){100, height / 2
			- app->active_scene->menus[0]->buttons[0]->height
			* app->active_scene->menus[0]->num_buttons / 2});
	}
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
