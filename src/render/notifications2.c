/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 23:37:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 23:38:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	should_render_border(int32_t xy[2], int32_t xy_min_max[2],
						t_vec2 pos, int32_t border_size)
{
	return (xy[0] >= xy_min_max[0] - border_size || xy[0] < (int32_t)pos[0] +
				border_size || xy[1] >= xy_min_max[1] - border_size || xy[1] <
					(int32_t)pos[1] + border_size);
}

static void		render_story_message(t_doom3d *app,
					t_notification *notification)
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

void			render_notifications_background(t_doom3d *app, t_vec2 pos,
					int32_t	dims[2], int32_t border_size)
{
	int32_t		x;
	int32_t		y;
	int32_t		y_max;
	int32_t		x_max;
	int32_t		idx;

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
				idx = y * app->window->framebuffer->width + x;
				app->window->framebuffer->buffer[idx] = CLEAR_COLOR;
				if (should_render_border((int32_t[2]){x, y},
					(int32_t[2]){x_max, y_max}, pos, border_size))
					app->window->framebuffer->buffer[idx] = 0xffffffff;
			}
		}
	}
}

void			render_notification_messages(t_doom3d *app, t_vec2 pos,
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
			window_text_render_shaded(app->window, (t_text_params){
				.text = notification->message,
				.text_color = (SDL_Color){255, 255, 0, 255}, .blend_ratio = 1.0,
				.xy = (int32_t[2]){pos[0] + padding + 2,
					pos[1] + i * (text_dims[1] + padding)}
			}, app->window->debug_font);
			i++;
		}
		else if (notification->type == notification_type_story)
			render_story_message(app, notification);
		node = node->next;
	}
}