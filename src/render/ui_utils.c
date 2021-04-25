/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:21:40 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 00:49:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Renders loading view text (and title text)
*/

void			render_loading_view(t_doom3d *app)
{
	int32_t	width;
	int32_t	height;

	width = app->window->framebuffer->width / 2;
	height = app->window->framebuffer->height / 2;
	render_ui_title(app);
	window_text_render_centered_shaded(app->window, (t_text_params){
		.text = "Loading",
		.blend_ratio = 1.0,
		.xy = (int32_t[2]){width, height},
		.text_color = (SDL_Color){255, 255, 255, 255}},
		app->window->main_font);
}

/*
** Renders dark overlay (e.g. pause view)
*/

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
		(int32_t[2]){pos[0], pos[1]}, 0.6);
}

/*
** Render button menu
*/

void			render_button_menu(t_button_group *menu, t_vec2 pos)
{
	if (menu == NULL)
		return ;
	if (pos[0] != menu->pos[0] || pos[1] != menu->pos[1])
	{
		button_group_update_position(menu, pos);
	}
	button_group_render(menu);
}

/*
** Renders UI title
*/

void			render_ui_title(t_doom3d *app)
{
	window_text_render_centered_shaded(app->window, (t_text_params){
			.text = "Doom-3D", .blend_ratio = 1.0,
			.xy = (int[2]){app->window->framebuffer->width / 2,
				FONT_SIZE * 2 + 10},
			.text_color = (SDL_Color){255, 0, 0, 255}},
			app->window->title_font);
}
