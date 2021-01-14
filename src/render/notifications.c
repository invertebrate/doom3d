/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:24:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/13 16:18:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		notifications_background_render(t_doom3d *app, t_vec2 pos,
					int32_t	dims[2], int32_t border_size)
{
	int32_t		x;
	int32_t		y;
	int32_t		y_max;
	int32_t		x_max;

	y_max = (int32_t)pos[1] + (int32_t)dims[1] + border_size * 2;
	x_max = (int32_t)pos[0] + (int32_t)dims[0] + border_size * 2;
	y = pos[1] - 1;
	while (++y < y_max)
	{
		x = pos[0] - 1;
		while (++x < (int32_t)pos[0] + (int32_t)dims[0] + border_size * 2)
		{
			if (y >= 0 && y < app->window->framebuffer->height &&
				x >= 0 && x < app->window->framebuffer->width)
			{
				app->window->framebuffer->buffer[
					y * app->window->framebuffer->width + x] =
						CLEAR_COLOR;
				if (x >= x_max - border_size ||
					x < (int32_t)pos[0] + border_size ||
					y >= y_max - border_size ||
					y < (int32_t)pos[1] + border_size)
					app->window->framebuffer->buffer[
					y * app->window->framebuffer->width + x] = 0xffffffff;
			}
		}
	}
}

static void		notification_messages_render(t_doom3d *app, t_vec2 pos,
					int32_t	text_dims[2], int32_t padding)
{
	int32_t			i;
	t_list			*node;
	t_notification	*notification;

	node = app->notifications;
	i = 0;
	while (node)
	{
		notification = node->content;
		if (notification->type == notification_type_info)
		{
			window_text_render(app->window, (t_text_params){
				.text = notification->message,
				.text_color = (SDL_Color){255, 255, 0, 255}, .blend_ratio = 1.0,
				.xy = (int32_t[2]){pos[0] + padding + 2,
					pos[1] + i * (text_dims[1] + padding)}
			}, app->window->debug_font);
			i++;
		}
		else if (notification->type == notification_type_story)
		{
			framebuffer_dark_overlay(app->window->framebuffer,
				app->window->framebuffer->width,
					app->window->framebuffer->height, (t_vec2){0, 0});
			window_text_render_centered(app->window, (t_text_params){
				.text = notification->message,
				.text_color = (SDL_Color){255, 0, 0, 255}, .blend_ratio = 1.0,
				.xy = (int32_t[2]){app->window->framebuffer->width / 2,
					app->window->framebuffer->height / 2 - 100}
			}, app->window->main_font);
		}
		node = node->next;
	}
}

void			notifications_render(t_doom3d *app, t_vec2 pos)
{
	int32_t		text_dims[2];
	int32_t		dims[2];
	int32_t		padding;
	int32_t		i;
	t_list		*node;

	if (app->notifications == NULL)
		return ;
	dims[0] = 0;
	dims[1] = 1;
	padding = 3;
	node = app->notifications;
	i = 0;
	while (node)
	{
		if (((t_notification*)node->content)->type == notification_type_info)
		{
			TTF_SizeText(app->window->debug_font,
				((t_notification*)node->content)->message,
				&text_dims[0], &text_dims[1]);
			dims[0] = (int32_t)l3d_fmax(dims[0], text_dims[0] + padding);
			dims[1] += text_dims[1] + padding;
			i++;
		}
		node = node->next;
	}
	while ((int32_t)pos[1] + dims[1] + padding * 2 < 0)
		pos[1]++;
	while ((int32_t)pos[0] + dims[0] + padding * 2 >
		app->window->framebuffer->width)
		pos[0]--;
	if (i > 0)
		notifications_background_render(app, pos, dims, padding);
	notification_messages_render(app, pos, text_dims, padding);
}