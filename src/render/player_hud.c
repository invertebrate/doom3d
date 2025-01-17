/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:12:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 12:38:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	render_vertical_crosshair_part(t_doom3d *app,
					int32_t offset, int32_t length, uint32_t color)
{
	l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
		app->window->framebuffer->height},
		(int32_t[2][2]){{app->window->framebuffer->width / 2,
		app->window->framebuffer_3d->height / 2 - (offset + length) + 32},
	{app->window->framebuffer->width / 2,
		app->window->framebuffer_3d->height / 2 - offset + 32}}, color);
	l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
		app->window->framebuffer->height},
		(int32_t[2][2]){{app->window->framebuffer->width / 2,
		app->window->framebuffer_3d->height / 2 + (offset + length) + 32},
	{app->window->framebuffer->width / 2,
		app->window->framebuffer_3d->height / 2 + offset + 32}}, color);
}

static void	render_crosshair(t_doom3d *app, int32_t offset, int32_t length,
					uint32_t color)
{
	render_vertical_crosshair_part(app, offset, length, color);
	l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
		app->window->framebuffer->height},
		(int32_t[2][2]){{app->window->framebuffer->width / 2
		+ offset, app->window->framebuffer_3d->height / 2 + 32},
	{app->window->framebuffer->width / 2 + (offset + length),
		app->window->framebuffer_3d->height / 2 + 32}}, color);
	l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
		app->window->framebuffer->height},
		(int32_t[2][2]){{app->window->framebuffer->width / 2
		- (offset + length), app->window->framebuffer_3d->height / 2 + 32},
	{app->window->framebuffer->width / 2 - offset,
		app->window->framebuffer_3d->height / 2 + 32}}, color);
}

static void	render_current_frame(t_anim_frame *curr_frame,
					t_surface *player_layer, t_surface *anim_source)
{
	int32_t				y;

	y = -1;
	while (++y < curr_frame->height)
	{
		ft_memcpy(player_layer->pixels + y * curr_frame->width,
			anim_source->pixels + anim_source->w
			* (curr_frame->y_offset + y) + curr_frame->x_offset + 2,
			sizeof(uint32_t) * curr_frame->width - 2);
	}
}

/*
** Based on current player animation, copy current frame from source image
** and render it on screen.
** ToDo: Remove if (app->player.equipped_weapon->id == weapon_shotgun)
** and leave only bottom l3d_image_place once we've unified our
** weapon animations.
*/

static void	render_player_animation(t_doom3d *app)
{
	t_surface			*anim_source;
	t_sprite_anim		*animation;
	t_anim_frame		*curr_frame;
	t_surface			player_layer;

	animation = &app->animations[app->player_hud.curr_animation];
	anim_source = get_animation_source(app);
	if (!anim_source)
		return ;
	curr_frame = &animation->frames[animation->current_frame];
	error_check(!(player_layer.pixels
			= ft_calloc(sizeof(uint32_t) * curr_frame->width
				* curr_frame->height)),
		"Failed to malloc player layer for animation");
	render_current_frame(curr_frame, &player_layer, anim_source);
	player_layer.w = curr_frame->width;
	player_layer.h = curr_frame->height;
	l3d_image_place(&(t_surface){.pixels = app->window->framebuffer->buffer,
		.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width},
		&player_layer, (int32_t[2]){app->window->framebuffer->width - 96 - 640,
		app->window->framebuffer->height - 76 - 360}, 1.0);
	free(player_layer.pixels);
}

void	render_hud(t_doom3d *app)
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
	if (!app->settings.is_third_person)
		render_player_animation(app);
	player_stats_render(app);
	render_crosshair(app, offset, length, 0xffffffff);
}
