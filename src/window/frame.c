/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:32:17 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/17 14:28:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			window_frame_clear(t_window *window)
{
	l3d_buffer_uint32_clear(window->framebuffer->buffer,
		window->framebuffer->width * window->framebuffer->height, CLEAR_COLOR);
}

void			window_frame_draw(t_window *window)
{
	SDL_UpdateTexture(window->frame, NULL, window->framebuffer->buffer,
		window->framebuffer->width * 4);
	SDL_RenderCopy(window->renderer, window->frame, NULL, NULL);
	SDL_RenderPresent(window->renderer);
}

static void		window_editor_framebuffer_recreate(t_window *window)
{
	t_framebuffer	*editor_view;
	int32_t			width;
	int32_t			height;

	editor_view = NULL;
	width = window->framebuffer->width / 4 * 3;
	height = window->framebuffer->height / 4 * 3;
	while (width % 4 != 0)
		width++;
	while (height % 4 != 0)
		height++;
	l3d_framebuffer_recreate(&editor_view, width, height);
	window->editor_pos[0] = window->framebuffer->width / 2 -
		editor_view->width / 2;
	window->editor_pos[1] = window->framebuffer->height / 2 -
		editor_view->height / 2;
	window->editor_framebuffer = editor_view;
}

void			window_frame_recreate(t_window *window)
{
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
