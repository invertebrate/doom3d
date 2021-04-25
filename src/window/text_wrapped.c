/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_wrapped.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:58:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 18:05:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Create text surface with wrapped (by line break) text
*/

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
		surface = surface_from_font_solid(params, font);
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

/*
** Render text on window centered and wrapped by line breaks
*/

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
		surface = surface_from_font_solid(params, font);
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

/*
** Render shaded text on window wrapped by line breaks
*/

void				window_text_render_wrapped_shaded(t_window *window,
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
		surface = surface_from_font_solid(params, font);
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

/*
** Render shaded and centered text on window wrapped by line breaks
*/

void				window_text_render_centered_wrapped_shaded(t_window *window,
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
		surface = surface_from_font_solid(params, font);
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
