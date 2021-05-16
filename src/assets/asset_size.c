/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 20:23:59 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 20:25:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	add_surface_size(void *val, void *params)
{
	t_surface	*surface;
	size_t		*counter;

	counter = params;
	surface = val;
	*counter += sizeof(t_surface);
	*counter += sizeof(uint32_t) * surface->w * surface->h;
}

static size_t	get_sdl_asset_size(SDL_RWops *asset)
{
	return (asset->size(asset));
}

size_t	get_assets_size(t_assets *assets)
{
	size_t	size_count;
	int32_t	i;

	size_count = 0;
	i = -1;
	while (++i < 6)
		add_surface_size(assets->skybox_textures[i], &size_count);
	hash_map_foreach(assets->sprite_textures, add_surface_size, &size_count);
	hash_map_foreach(assets->hud_textures, add_surface_size, &size_count);
	hash_map_foreach(assets->textures, add_surface_size, &size_count);
	hash_map_foreach(assets->normal_maps, add_surface_size, &size_count);
	i = -1;
	while (++i < SOUNDS_NUM_TRACKS)
		size_count += get_sdl_asset_size(assets->sounds[i]);
	size_count += get_sdl_asset_size(assets->main_font);
	size_count += get_sdl_asset_size(assets->title_font);
	size_count += get_sdl_asset_size(assets->small_font);
	return (size_count);
}
