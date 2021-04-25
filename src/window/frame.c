/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:32:17 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 18:04:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Clear frame
*/

void			window_frame_clear(t_window *window)
{
	l3d_buffer_uint32_clear(window->framebuffer->buffer,
		window->framebuffer->width * window->framebuffer->height, CLEAR_COLOR);
}

/*
** Draw window frame onto window
*/

void			draw_window_frame(t_window *window)
{
	SDL_UpdateTexture(window->frame, NULL, window->framebuffer->buffer,
		window->framebuffer->width * 4);
	SDL_RenderCopy(window->renderer, window->frame, NULL, NULL);
	SDL_RenderPresent(window->renderer);
}

static void		window_editor_framebuffer_recreate(t_window *window)
{
	int	width;
	int	height;

	width = window->framebuffer->width * 5 / 6;
	height = window->framebuffer->height * 6 / 7;
	while (width % 4 != 0)
		width++;
	while (height % 4 != 0)
		height++;
	l3d_framebuffer_recreate(&window->editor_framebuffer, width, height);
	window->editor_pos[0] = window->framebuffer->width - width - 10;
	window->editor_pos[1] = 10;
}

/*
** Create frame after e.g. resize
*/

void			window_frame_recreate(t_window *window)
{
	LOG_INFO("Recreate frame %d %d", window->width, window->height);
	if (window->frame != NULL)
		SDL_DestroyTexture(window->frame);
	window->frame = SDL_CreateTexture(window->renderer,
		PIXEL_FORMAT, SDL_TEXTUREACCESS_STREAMING, window->width,
		window->height);
	error_check(window->frame == NULL, SDL_GetError());
	l3d_framebuffer_recreate(&window->framebuffer,
		window->width, window->height);
	window_editor_framebuffer_recreate(window);
}
