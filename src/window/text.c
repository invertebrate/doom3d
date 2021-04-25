/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 18:00:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Render text on window
*/

void				window_text_render(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font_solid(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer
		}, &(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels}, params.xy, params.blend_ratio);
	SDL_FreeSurface(surface);
}

/*
** Render text on window so it is centered
*/

void				window_text_render_centered(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font_solid(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer},
		&(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels},
		(int[2]){params.xy[0] - surface->w / 2, params.xy[1] - surface->h / 2},
		params.blend_ratio);
	SDL_FreeSurface(surface);
}

/*
** Render shaded text on window
*/

void				window_text_render_shaded(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font_solid(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer
		}, &(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels}, params.xy, params.blend_ratio);
	SDL_FreeSurface(surface);
}

/*
** Render centered shaded text on window
*/

void				window_text_render_centered_shaded(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font_solid(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer},
		&(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels},
		(int[2]){params.xy[0] - surface->w / 2, params.xy[1] - surface->h / 2},
		params.blend_ratio);
	SDL_FreeSurface(surface);
}
