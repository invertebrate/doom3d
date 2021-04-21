/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_button_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 22:51:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 20:21:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Converts sdl surface to t_surface
*/
t_surface			*convert_sdl_surface_to_t_surface(SDL_Surface *src)
{
	t_surface	*dst;

	error_check(!(dst = ft_calloc(sizeof(t_surface))),
		"Failed to malloc surface");
	error_check(!(dst->pixels = ft_calloc(sizeof(uint32_t) *
		src->w * src->h)), "Failed to malloc surface pixels");
	ft_memcpy(dst->pixels, src->pixels,
		sizeof(uint32_t) * src->w * src->h);
	dst->w = src->w;
	dst->h = src->h;
	return (dst);
}

t_surface			*menu_button_surface_shaded(const char *option,
						TTF_Font *font)
{
	SDL_Surface	*tmp_surface;
	t_surface	*surface;

	tmp_surface = surface_from_font_shaded(
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 0, 0, 255}}, font);
	surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (surface);
}

t_surface			*menu_button_down_surface_shaded(const char *option,
						TTF_Font *font)
{
	SDL_Surface	*tmp_surface;
	t_surface	*down_surface;

	tmp_surface = surface_from_font_shaded(
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 255, 255, 255}},
		font);
	down_surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (down_surface);
}

t_surface			*menu_button_surface(const char *option,
						TTF_Font *font)
{
	SDL_Surface	*tmp_surface;
	t_surface	*surface;

	tmp_surface = surface_from_font_solid(
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 0, 0, 255}}, font);
	surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (surface);
}

t_surface			*menu_button_down_surface(const char *option,
						TTF_Font *font)
{
	SDL_Surface	*tmp_surface;
	t_surface	*down_surface;

	tmp_surface = surface_from_font_solid(
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 255, 255, 255}},
		font);
	down_surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (down_surface);
}
