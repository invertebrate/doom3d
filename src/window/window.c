/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:13:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Resize window
*/

void	window_resize(t_window *window, int32_t width, int32_t height)
{
	SDL_SetWindowSize(window->window, width, height);
	window->width = width;
	window->height = height;
	SDL_SetWindowPosition(window->window,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	window->resized = true;
}

/*
** Callback for window hidden and resize events so the window struct
** will know when it gets resized
*/

static int	window_resize_callback(void *data, SDL_Event *event)
{
	t_window	*window;

	if (event->type == SDL_WINDOWEVENT
		&& (event->window.event == SDL_WINDOWEVENT_RESIZED
			|| event->window.event == SDL_WINDOWEVENT_MINIMIZED
			|| event->window.event == SDL_WINDOWEVENT_MAXIMIZED
			|| event->window.event == SDL_WINDOWEVENT_SHOWN
			|| event->window.event == SDL_WINDOWEVENT_HIDDEN))
	{
		window = (t_window *)data;
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

static void	window_set_fonts(t_window *window)
{
	window->main_font = TTF_OpenFont(GAME_FONT, FONT_SIZE);
	error_check(window->main_font == NULL, TTF_GetError());
	window->debug_font = TTF_OpenFont(DEBUG_FONT, FONT_SIZE * 0.36);
	error_check(window->debug_font == NULL, TTF_GetError());
	window->title_font = TTF_OpenFont(GAME_FONT, FONT_SIZE * 2);
	error_check(window->title_font == NULL, TTF_GetError());
}

/*
** Create new window with framebuffers
*/

void	window_create(t_window **window_ref,
			int32_t width, int32_t height)
{
	t_window	*window;

	error_check((window = (t_window *)ft_calloc(sizeof(t_window))) == NULL,
		"Window ft_calloc failed");
	window->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, 0);
	window->width = width;
	window->height = height;
	error_check(window->window == NULL, SDL_GetError());
	window->renderer
		= SDL_CreateRenderer(window->window, -1, SDL_RENDERER_SOFTWARE);
	error_check(window->renderer == NULL, SDL_GetError());
	window->window_id = SDL_GetWindowID(window->window);
	window->is_hidden = false;
	window->frame = NULL;
	window->framebuffer = NULL;
	window->editor_framebuffer = NULL;
	window_set_fonts(window);
	window_frame_recreate(window);
	SDL_AddEventWatch(window_resize_callback, window);
	window->resized = false;
	window->is_fullscreen = false;
	*window_ref = window;
}

/*
** Destroy window
*/

void	window_destroy(t_window *window)
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
