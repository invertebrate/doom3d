/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/16 16:21:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		ui_title_render(t_doom3d *app)
{
	window_text_render_centered(app->window, (t_text_params){
			.text = "Doom-3D", .blend_ratio = 1.0,
			.xy = (int[2]){app->window->framebuffer->width / 2,
				FONT_SIZE * 2 + 10},
			.text_color = (SDL_Color){255, 0, 0, 255}},
			app->window->title_font);
}

void			framebuffer_dark_overlay(t_framebuffer *framebuffer,
					int32_t width, int32_t height, t_vec2 pos)
{
	uint32_t	dark[width * height];
	int32_t		i;

	i = -1;
	while (++i < width * height)
		dark[i] = 0x000000FF;
	l3d_image_place(&(t_surface){.pixels = framebuffer->buffer,
			.h = framebuffer->height, .w = framebuffer->width},
		&(t_surface){.pixels = dark, .w = width, .h = height},
		(int32_t[2]){pos[0], pos[1]}, 0.5);
}

void			menu_render(t_doom3d *app, t_vec2 pos)
{
	if (pos[0] != app->active_scene->menu->pos[0] ||
		pos[1] != app->active_scene->menu->pos[1])
	{
		button_group_update_position(app->active_scene->menu, pos);
	}
	button_group_render(app->active_scene->menu);
}

void			ui_render(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_menu ||
		app->active_scene->scene_id == scene_id_main_menu_settings)
		menu_render(app, (t_vec2){app->window->framebuffer->width / 2 -
			app->active_scene->menu->buttons[0]->width / 2,
			200});
	else if (app->active_scene->scene_id == scene_id_main_game)
	{
		hud_render(app);
		if (app->active_scene->is_paused)
		{
			framebuffer_dark_overlay(app->window->framebuffer,
				app->window->framebuffer->width,
					app->window->framebuffer->height, (t_vec2){0, 0});
			menu_render(app, (t_vec2){app->window->framebuffer->width / 2 -
				app->active_scene->menu->buttons[0]->width / 2,
				200});
		}
	}
	else if (app->active_scene->scene_id == scene_id_editor3d)
	{
		menu_render(app, (t_vec2){10, 0});
	}
}

void			loading_render(t_doom3d *app)
{
	ui_title_render(app);
	window_text_render_centered(app->window, (t_text_params){
		.text = "Loading...",
		.blend_ratio = 1.0,
		.xy = (int32_t[2]){app->window->framebuffer->width / 2,
			app->window->framebuffer->height / 2},
		.text_color = (SDL_Color){255, 255, 255, 255}},
		app->window->main_font);
}
