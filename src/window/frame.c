/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:32:17 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/06 13:24:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Clear frame
*/

void	window_frame_clear(t_window *window)
{
	l3d_buffer_uint32_clear(window->framebuffer->buffer,
		window->framebuffer->width * window->framebuffer->height, CLEAR_COLOR);
}

/*
** Draw window frame onto window
*/

void	draw_window_frame(t_window *window)
{
	SDL_UpdateTexture(window->frame, NULL, window->framebuffer->buffer,
		window->framebuffer->width * 4);
	SDL_RenderCopy(window->renderer, window->frame, NULL, NULL);
	SDL_RenderPresent(window->renderer);
}

void	window_3d_framebuffer_recreate(t_window *window, int32_t dims[2],
			int32_t pos[2])
{
	error_check(dims[0] % 4 != 0 || dims[1] % 4 != 0,
		"3d framebuffer dimensions invalid. It should be dividible by 4");
	l3d_framebuffer_recreate(&window->framebuffer_3d, dims[0], dims[1]);
	window->view_3d_pos[0] = pos[0];
	window->view_3d_pos[1] = pos[1];
}

/*
** Create frame after e.g. resize
*/

void	window_frame_recreate(t_window *window)
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
}
