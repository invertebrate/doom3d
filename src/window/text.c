/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 18:20:10 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

SDL_Surface			*surface_from_font(t_text_params params,
						TTF_Font *font)
{
	SDL_Surface		*text_surface;
	SDL_Surface		*formatted_surface;

	text_surface = TTF_RenderText_Solid(font,
		params.text, params.text_color);
	error_check(!text_surface, TTF_GetError());
	formatted_surface = SDL_ConvertSurfaceFormat(text_surface,
		PIXEL_FORMAT, 0);
	SDL_FreeSurface(text_surface);
	error_check(!formatted_surface, SDL_GetError());
	return (formatted_surface);
}

void				window_text_render_wrapped(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;
	char		**parts;
	int32_t		i;
	int32_t		height;

	parts = ft_strsplit(params.text, '\n');
	if (parts == NULL)
		return ;
	TTF_SizeText(font, parts[0], NULL, &height);
	i = 0;
	while (parts[i])
	{
		params.text = parts[i];
		surface = surface_from_font(params, font);
		l3d_image_place(&(t_surface){.h = window->framebuffer->height,
			.w = window->framebuffer->width,
			.pixels = window->framebuffer->buffer
			}, &(t_surface){.h = surface->h,
			.w = surface->w,
			.pixels = surface->pixels}, (int32_t[2]){
				params.xy[0], params.xy[1] + i * height}, params.blend_ratio);
		SDL_FreeSurface(surface);
		ft_strdel(&parts[i++]);
	}
	free(parts);
}

void				window_text_render(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font(params, font);
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width,
		.pixels = window->framebuffer->buffer
		}, &(t_surface){.h = surface->h,
		.w = surface->w,
		.pixels = surface->pixels}, params.xy, params.blend_ratio);
	SDL_FreeSurface(surface);
}

void				window_text_render_centered(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;

	surface = surface_from_font(params, font);
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

void				window_text_render_centered_wrapped(t_window *window,
						t_text_params params, TTF_Font *font)
{
	SDL_Surface	*surface;
	char		**parts;
	int32_t		i;
	int32_t		height;

	parts = ft_strsplit(params.text, '\n');
	if (parts == NULL)
		return ;
	TTF_SizeText(font, parts[0], NULL, &height);
	i = 0;
	while (parts[i])
	{
		params.text = parts[i];
		surface = surface_from_font(params, font);
		l3d_image_place(&(t_surface){.h = window->framebuffer->height,
			.w = window->framebuffer->width,
			.pixels = window->framebuffer->buffer},
			&(t_surface){.h = surface->h,
			.w = surface->w, .pixels = surface->pixels},
			(int[2]){params.xy[0] - surface->w / 2,
			params.xy[1] - surface->h / 2 + i * height}, params.blend_ratio);
		SDL_FreeSurface(surface);	
		ft_strdel(&parts[i++]);
	}
	free(parts);
}
