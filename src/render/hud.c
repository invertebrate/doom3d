/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:12:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/11 18:39:54 by ohakola          ###   ########.fr       */
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

// static void		player_animation_render(t_doom3d *app)
// {
// 	t_sprite_anim		*animation;
// 	int32_t				dims[2];
// 	t_surface			player_layer;

// 	animation = &app->animations[app->player_hud.player_animation];
// 	dims[0] = animation->frame_width;
// 	dims[1] = animation->frame_height;
// 	error_check(!(player_layer.pixels =
// 		ft_calloc(sizeof(uint32_t) * dims[0] * dims[1])),
// 		"Failed to malloc player layer for animation");
// 	l3d_image_place(&player_layer, animation->source,
// 			(int32_t[2]){0, -dims[0] * animation->current_frame}, 1.0);
// 	l3d_image_place(&(t_surface){
// 			.pixels = app->window->framebuffer->buffer,
// 			.h = app->window->framebuffer->height,
// 			.w = app->window->framebuffer->width},
// 			&player_layer,
// 			(int32_t[2]){0, 0}, 1.0);
// 	free(player_layer.pixels);
// }

void			hud_render(t_doom3d *app)
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
	// player_animation_render(app);
	crosshair_render(app, offset, length, 0xffffffff);
}
