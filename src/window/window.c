/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/17 13:55:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			window_resize(t_window *window, int32_t width, int32_t height)
{
	SDL_SetWindowSize(window->window, width, height);
	window->width = width;
	window->height = height;
	SDL_SetWindowPosition(window->window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	window->resized = true;
}

static int		window_resize_callback(void *data, SDL_Event *event)
{
	t_window	*window;

	if (event->type == SDL_WINDOWEVENT &&
		(event->window.event == SDL_WINDOWEVENT_RESIZED ||
		event->window.event == SDL_WINDOWEVENT_MINIMIZED ||
		event->window.event == SDL_WINDOWEVENT_MAXIMIZED ||
		event->window.event == SDL_WINDOWEVENT_SHOWN ||
		event->window.event == SDL_WINDOWEVENT_HIDDEN))
	{
		window = (t_window*)data;
		if (event->window.windowID == window->window_id)
		{
			window->resized = true;
			SDL_GetWindowSize(window->window, &window->width,
				&window->height);
			if (event->window.event == SDL_WINDOWEVENT_HIDDEN)
				window->is_hidden = true;
			else if (event->window.event == SDL_WINDOWEVENT_SHOWN)
				window->is_hidden = false;
		}
	}
	return (0);
}

void			window_create(t_window **window_ref,
					int32_t width, int32_t height)
{
	t_window *window;

	error_check((window = (t_window*)malloc(sizeof(t_window))) == NULL,
		"Window malloc failed");
	window->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, 0);
	window->width = width;
	window->height = height;
	error_check(window->window == NULL, SDL_GetError());
	window->renderer =
		SDL_CreateRenderer(window->window, -1, SDL_RENDERER_SOFTWARE);
	error_check(window->renderer == NULL, SDL_GetError());
	window->window_id = SDL_GetWindowID(window->window);
	window->is_hidden = false;
	window->frame = NULL;
	window->framebuffer = NULL;
	window->main_font = NULL;
	window->debug_font = NULL;
	window->title_font = NULL;
	window_frame_recreate(window);
	SDL_AddEventWatch(window_resize_callback, window);
	window->resized = false;
	window->is_fullscreen = false;
	*window_ref = window;
}

void			window_destroy(t_window *window)
{
	l3d_framebuffer_destroy(window->framebuffer);
	l3d_framebuffer_destroy(window->editor_framebuffer);
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->window);
	TTF_CloseFont(window->main_font);
	TTF_CloseFont(window->debug_font);
	TTF_CloseFont(window->title_font);
	free(window);
}
