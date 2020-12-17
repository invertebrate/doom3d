/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/17 14:34:10 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

SDL_Surface			*surface_from_font(t_window *window, t_text_params params,
						TTF_Font *font)
{
	SDL_Surface		*text_surface;
	SDL_Surface		*formatted_surface;

	text_surface = TTF_RenderText_Blended_Wrapped(font,
		params.text, params.text_color, window->width);
	error_check(!text_surface, TTF_GetError());
	formatted_surface = SDL_ConvertSurfaceFormat(text_surface,
		PIXEL_FORMAT, 0);
	SDL_FreeSurface(text_surface);
	error_check(!formatted_surface, SDL_GetError());
	return (formatted_surface);
}

void				window_text_render(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font(window, params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer
		},
		&(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels}, params.xy, params.blend_ratio);
	SDL_FreeSurface(surface);
}

void				window_text_render_centered(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font(window, params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer},
		&(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels},
		(int[2]){params.xy[0] - surface->w / 2, params.xy[1] - surface->h / 2},
		1.0);
	SDL_FreeSurface(surface);
}
