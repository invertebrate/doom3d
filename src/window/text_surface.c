/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:00:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:18:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Create text surface with shaded font
*/

SDL_Surface	*surface_from_font_shaded(t_text_params params,
				TTF_Font *font)
{
	SDL_Surface		*text_surface;
	SDL_Surface		*formatted_surface;
	uint32_t		rgba[4];

	l3d_u32_to_rgba(CLEAR_COLOR, rgba);
	text_surface = TTF_RenderText_Shaded(font,
			params.text, params.text_color,
			(SDL_Color){rgba[0], rgba[1], rgba[2], 0});
	error_check(!text_surface, TTF_GetError());
	formatted_surface = SDL_ConvertSurfaceFormat(text_surface,
			PIXEL_FORMAT, 0);
	SDL_FreeSurface(text_surface);
	error_check(!formatted_surface, SDL_GetError());
	return (formatted_surface);
}

/*
** Create text surface with solid font
*/

SDL_Surface	*surface_from_font_solid(t_text_params params,
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
