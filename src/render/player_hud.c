/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:12:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/12 15:52:45 by ohakola          ###   ########.fr       */
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

static void		player_animation_render(t_doom3d *app)
{
	t_surface			*anim_source;
	t_sprite_anim		*animation;
	t_anim_frame		*curr_frame;
	t_surface			player_layer;
	int32_t				y;

	animation = &app->animations[app->player_hud.curr_animation];
	if (!(anim_source = get_animation_source(app)))
		return ;
	curr_frame = &animation->frames[animation->current_frame];
	error_check(!(player_layer.pixels =
		ft_calloc(sizeof(uint32_t) * curr_frame->width * curr_frame->height)),
		"Failed to malloc player layer for animation");
	y = -1;
	while (++y < curr_frame->height)
	{
		ft_memcpy(player_layer.pixels + y * curr_frame->width,
			anim_source->pixels + anim_source->w *
				(curr_frame->y_offset + y) + curr_frame->x_offset,
			sizeof(uint32_t) * curr_frame->width);
	}
	player_layer.w = curr_frame->width;
	player_layer.h = curr_frame->height;
	if (app->player.equipped_weapon->id == weapon_shotgun)
		l3d_image_place(&(t_surface){
			.pixels = app->window->framebuffer->buffer,
			.h = app->window->framebuffer->height,
			.w = app->window->framebuffer->width}, &player_layer,
			(int32_t[2]){app->window->framebuffer->width / 2,
				app->window->framebuffer->height - curr_frame->height}, 1.0);
	else
		l3d_image_place(&(t_surface){
			.pixels = app->window->framebuffer->buffer,
			.h = app->window->framebuffer->height,
			.w = app->window->framebuffer->width}, &player_layer,
			(int32_t[2]){app->window->framebuffer->width / 2 -
				curr_frame->width / 2,
				app->window->framebuffer->height - curr_frame->height}, 1.0);
	free(player_layer.pixels);
}

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
	player_animation_render(app);
	crosshair_render(app, offset, length, 0xffffffff);
}
