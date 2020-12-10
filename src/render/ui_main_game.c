/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_main_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:12:01 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/10 15:39:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		cross_hair_vertical_render(t_doom3d *app,
					int32_t offset, int32_t length, uint32_t color)
{
	l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
			app->window->framebuffer->height},
		(int32_t[2][2]){{app->window->framebuffer->width / 2,
			app->window->framebuffer->height / 2 - (offset + length)},
		{app->window->framebuffer->width / 2,
			app->window->framebuffer->height / 2 - offset}}, color);
	l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
			app->window->framebuffer->height},
		(int32_t[2][2]){{app->window->framebuffer->width / 2,
			app->window->framebuffer->height / 2 + (offset + length)},
		{app->window->framebuffer->width / 2,
			app->window->framebuffer->height / 2 + offset}}, color);
}

static void		crosshair_render(t_doom3d *app, int32_t offset, int32_t length,
					uint32_t color)
{
	cross_hair_vertical_render(app, offset, length, color);
	l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
			app->window->framebuffer->height},
		(int32_t[2][2]){{app->window->framebuffer->width / 2 +
			offset, app->window->framebuffer->height / 2},
		{app->window->framebuffer->width / 2 + (offset + length),
			app->window->framebuffer->height / 2}}, color);
	l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
			app->window->framebuffer->height},
		(int32_t[2][2]){{app->window->framebuffer->width / 2 -
			(offset + length), app->window->framebuffer->height / 2},
		{app->window->framebuffer->width / 2 - offset,
			app->window->framebuffer->height / 2}}, color);
}

void			ui_main_game_render(t_doom3d *app)
{
	int32_t	offset;
	int32_t	length;

	offset = 0;
	length = 10;
	if (app->player.is_moving)
		offset += 5;
	if (app->player.is_running)
		offset += 5;
	if (app->player.is_shooting)
		offset += 5;
	crosshair_render(app, offset, length, 0xffffffff);
}
