/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_load_from_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 22:13:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/20 00:18:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Skybox does not have file names written... (thus separate from read surface)
*/

static uint32_t	read_skybox(t_doom3d *app,
					t_file_contents *file, int32_t offset)
{
	int32_t		i;
	t_surface	*surface;
	uint32_t	*pixels;
	uint32_t	pixels_size;

	i = -1;
	while (++i < 6)
	{
		error_check(!(surface = ft_calloc(sizeof(t_surface))),
			"Failed to alloc surface");
		ft_memcpy(surface, file->buf + offset, sizeof(t_surface));
		offset += sizeof(t_surface);
		pixels_size = sizeof(uint32_t) * surface->w * surface->h;
		error_check(!(pixels = ft_calloc(pixels_size)),
			"Failed to allc pixels");
		ft_memcpy(pixels, file->buf + offset, pixels_size);
		surface->pixels = pixels;
		offset += pixels_size;
		app->assets.skybox_textures[i] = surface;
		if (app->is_debug)
			LOG_DEBUG("Read skybox of size %d %d, i: %d",
				surface->w, surface->h, i);
	}
	return (offset);
}

static void	validate_assets_file(t_file_contents *file)
{
	char			map_header[7];

	if (!file)
	{
		LOG_FATAL("Asset file (first map) NULL");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(&map_header, file->buf, 7);
	if (!ft_strequ(map_header, "ASSETS"))
		error_check(true, "Invalid asset file. First map must start ASSETS. "
			"You can convert an old map to contain assets with"
			" --convert-assets");
}

static void	validate_read_assets(uint32_t size_offset,
				uint32_t read_asset_offset, char map_header[128])
{
	if (read_asset_offset != size_offset || !ft_strequ(map_header, "MAP"))
	{
		LOG_FATAL("Asset read failure:"
			" Read %d, should've read %d, map header: %s",
			read_asset_offset, size_offset, map_header);
		exit(EXIT_FAILURE);
	}
}

void	load_assets_from_first_level(t_doom3d *app)
{
	t_file_contents	*file;
	char			char_buf[128];
	int32_t			offset;
	uint32_t		size_offset;
	uint32_t		read_asset_offset;

	ft_memset(char_buf, 0, sizeof(char_buf));
	ft_sprintf(char_buf, "maps/%s", FIRST_LEVEL);
	LOG_INFO("Load assets from first level (%s)", char_buf);
	file = read_file(char_buf);
	validate_assets_file(file);
	offset = 7;
	ft_memcpy(&size_offset, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	offset = read_skybox(app, file, offset);
	offset = read_texture_assets(app, file, offset);
	offset = read_model_assets(app, file, offset);
	offset = read_sdl_assets(app, file, offset);
	read_asset_offset = offset - 7 - sizeof(uint32_t);
	ft_memset(char_buf, 0, sizeof(char_buf));
	ft_memcpy(&char_buf, file->buf + offset, 4);
	validate_read_assets(size_offset, read_asset_offset, char_buf);
	destroy_file_contents(file);
}
