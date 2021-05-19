/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:21:20 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 16:22:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	load_fonts(t_assets *assets)
{
	assets->main_font = sdl_asset_as_memory(GAME_FONT);
	assets->small_font = sdl_asset_as_memory(DEBUG_FONT);
	assets->title_font = sdl_asset_as_memory(GAME_FONT);
}

void	fonts_destroy(t_assets *assets)
{
	SDL_RWclose(assets->main_font);
	SDL_RWclose(assets->small_font);
	SDL_RWclose(assets->title_font);
}
