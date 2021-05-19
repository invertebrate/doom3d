/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:21:20 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 18:09:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	load_fonts(t_assets *assets)
{
	sdl_asset_as_memory(GAME_FONT, &assets->main_font);
	sdl_asset_as_memory(DEBUG_FONT, &assets->small_font);
	sdl_asset_as_memory(GAME_FONT, &assets->title_font);
}

void	fonts_destroy(t_assets *assets)
{
	free(assets->main_font.data);
	free(assets->small_font.data);
	free(assets->title_font.data);
}
