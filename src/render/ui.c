/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/15 18:52:14 by ohakola          ###   ########.fr       */
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

static void		ui_menu_render(t_doom3d *app)
{
	int32_t			row_height;
	int32_t			y;
	int32_t			i;
	int32_t			selected_option;

	ui_title_render(app);
	row_height = 2 * FONT_SIZE;
	y = app->window->framebuffer->height / 1.75 - row_height;
	selected_option = app->active_scene->selected_option;
	i = -1;
	while (++i < app->active_scene->menu_option_count)
		window_text_render_centered(app->window, (t_text_params){
			.text = app->active_scene->menu_options[i],
			.blend_ratio = 1.0,
			.xy =
			(int[2]){app->window->framebuffer->width / 2, y + i * row_height},
			.text_color = selected_option == i ?
			(SDL_Color){255, 255, 255, 255} : (SDL_Color){255, 0, 0, 255}},
			app->window->main_font);
}

void			ui_render(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_menu ||
		app->active_scene->scene_id == scene_id_main_menu_settings)
		ui_menu_render(app);
	else if (app->active_scene->scene_id == scene_id_main_game)
	{
		ui_main_game_render(app);
		if (app->active_scene->is_paused)
		{
			framebuffer_dark_overlay(app->window->framebuffer,
				app->window->framebuffer->width,
					app->window->framebuffer->height, (t_vec2){0, 0});
			ui_menu_render(app);
		}
	}
	else if (app->active_scene->scene_id == scene_id_editor)
	{
		window_text_render_centered(app->window, (t_text_params){
			.text = "Editor", .blend_ratio = 1.0,
			.xy = (int32_t[2]){50, 60},
			.text_color = (SDL_Color){255, 0, 0, 255}},
			app->window->main_font);
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
