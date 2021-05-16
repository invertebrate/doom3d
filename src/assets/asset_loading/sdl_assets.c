/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:49:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/17 00:35:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Allocates space for an SDL loaded file to be saved into memory.
** These SDL_Rwops must be freed manually using free
*/

SDL_RWops	*sdl_asset_as_memory(const char *filename)
{
	SDL_RWops	*rw_file;
	size_t		size;
	void		*buffer;

	rw_file = SDL_RWFromFile(filename, "rb");
	size = rw_file->size(rw_file);
	buffer = ft_calloc(size);
	error_check(!buffer, "Failed to malloc font buffer");
	rw_file->read(rw_file, buffer, 1, size);
	rw_file->close(rw_file);
	return (SDL_RWFromConstMem(buffer, size));
}

/*
** Size for writing thus one byte for len + actual size
*/

static uint32_t	get_sdl_asset_write_size(SDL_RWops *asset)
{
	return (sizeof(uint32_t) + asset->size(asset));
}

uint32_t	get_sdl_assets_write_size(t_assets *assets)
{
	uint32_t	i;
	uint32_t	size_count;

	size_count = 0;
	i = -1;
	while (++i < SOUNDS_NUM_TRACKS)
		size_count += get_sdl_asset_write_size(assets->sounds[i]);
	size_count += get_sdl_asset_write_size(assets->main_font);
	size_count += get_sdl_asset_write_size(assets->title_font);
	size_count += get_sdl_asset_write_size(assets->small_font);
	return (size_count);
}

void	write_sdl_assets(int32_t fd, t_assets *assets)
{
	uint32_t	i;
	uint32_t	size;
	int32_t		ret;

	i = -1;
	while (++i < SOUNDS_NUM_TRACKS)
	{
		size = assets->sounds[i]->size(assets->sounds[i]);
		ret = write(fd, &size, sizeof(uint32_t));
		ret = write(fd, assets->sounds[i], size);
	}
	size = assets->main_font->size(assets->main_font);
	ret = write(fd, &size, sizeof(uint32_t));
	ret = write(fd, assets->main_font, size);
	size = assets->title_font->size(assets->title_font);
	ret = write(fd, &size, sizeof(uint32_t));
	ret = write(fd, assets->title_font, size);
	size = assets->small_font->size(assets->small_font);
	ret = write(fd, &size, sizeof(uint32_t));
	ret = write(fd, assets->small_font, size);
}
