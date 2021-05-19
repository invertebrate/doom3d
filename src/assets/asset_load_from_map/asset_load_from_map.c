/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_load_from_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 22:13:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 13:11:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Skybox does not have file names written... (thus separate from read surface)
*/

static uint32_t	read_skybox(t_doom3d *app, t_file_contents *file, int32_t offset)
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
		ft_memcpy(&surface, file->buf + offset, sizeof(t_surface));
		offset += sizeof(t_surface);
		pixels_size = sizeof(uint32_t) * surface->w * surface->h;
		error_check(!(pixels = ft_calloc(pixels_size)), "Failed to allc pixels");
		ft_memcpy(&pixels, file->buf + offset, pixels_size);
		surface->pixels = pixels;
		offset += pixels_size;
		app->assets.skybox_textures[i] = surface;
	}
	return (offset);
}

static void	validate_assets_file(t_file_contents *file)
{
	char			map_header[8];
	uint32_t		offset;

	if (!file)
	{
		LOG_FATAL("Asset file (first map) NULL");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(&map_header, file->buf, 8);
	offset = 8;
	if (!ft_strequ(map_header, "ASSETS\0"))
		error_check(true, "Invalid asset file. First map must start ASSETS\0");
}

void	load_assets_from_first_level(t_doom3d *app)
{
	t_file_contents	*file;
	char			filename[128];
	int32_t			offset;

	ft_sprintf(filename, "assets/map_data/%s", FIRST_LEVEL);
	LOG_INFO("Load assets from first level (%s)", filename);
	file = read_file(filename);
	validate_assets_file(file);
	offset = 8 + sizeof(uint32_t);
	offset = read_skybox(app, file, offset);
	offset = read_texture_assets(app, file, offset);
}
