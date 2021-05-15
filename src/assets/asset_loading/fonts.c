/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:21:20 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 22:47:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	fonts_load(t_assets *assets)
{
	assets->main_font = sdl_asset_as_memory(GAME_FONT);
	assets->small_font = sdl_asset_as_memory(DEBUG_FONT);
	assets->title_font = sdl_asset_as_memory(GAME_FONT);
}

void	fonts_destroy(t_assets *assets)
{
	free(assets->main_font);
	free(assets->small_font);
	free(assets->title_font);
}
