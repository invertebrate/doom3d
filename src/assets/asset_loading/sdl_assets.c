/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:49:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/20 19:51:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Allocates space for an SDL loaded file to be saved into memory.
*/

void	sdl_asset_as_memory(const char *filename, t_sized_file *file)
{
	SDL_RWops		*rw_file;
	size_t			size;

	rw_file = SDL_RWFromFile(filename, "rb");
	size = rw_file->size(rw_file);
	file->data = ft_calloc(size);
	error_check(!file->data, "Failed to malloc sdl buffer");
	rw_file->read(rw_file, file->data, 1, size);
	rw_file->close(rw_file);
	file->size = size;
}

uint32_t	get_sdl_assets_write_size(t_assets *assets)
{
	uint32_t	i;
	uint32_t	size_count;

	size_count = 0;
	size_count += sizeof(uint32_t);
	i = -1;
	while (++i < SOUNDS_NUM_TRACKS)
		size_count += get_sdl_asset_write_size(&assets->sounds[i]);
	size_count += get_sdl_asset_write_size(&assets->main_font);
	size_count += get_sdl_asset_write_size(&assets->title_font);
	size_count += get_sdl_asset_write_size(&assets->small_font);
	return (size_count);
}

static int32_t	write_safe(int32_t fd, t_sized_file *file)
{
	int32_t		ret;

	ret = write(fd, file->data, file->size);
	if (ret == -1)
	{
		LOG_FATAL("Failed to write map assets to map,"
			" use `git checkout %s`"
			" to delete malformed changes", FIRST_LEVEL);
		return (0);
	}
	return (ret);
}

/*
** Note that we make an assumption that we'll have 3 fonts, no more...
*/

static void	write_fonts(int32_t fd, t_assets *assets, int32_t *ret)
{
	*ret += write(fd, &assets->main_font.size, sizeof(uint32_t));
	*ret += write_safe(fd, &assets->main_font);
	*ret += write(fd, &assets->title_font.size, sizeof(uint32_t));
	*ret += write_safe(fd, &assets->title_font);
	*ret += write(fd, &assets->small_font.size, sizeof(uint32_t));
	*ret += write_safe(fd, &assets->small_font);
}

void	write_sdl_assets(int32_t fd, t_assets *assets, int32_t *ret)
{
	uint32_t	i;
	uint32_t	num_tracks;

	num_tracks = SOUNDS_NUM_TRACKS;
	*ret += write(fd, &num_tracks, sizeof(uint32_t));
	i = -1;
	while (++i < num_tracks)
	{
		*ret += write(fd, &assets->sounds[i].size, sizeof(uint32_t));
		*ret += write_safe(fd, &assets->sounds[i]);
	}
	write_fonts(fd, assets, ret);
}
