/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_load_from_map_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:05:55 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 13:08:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Returns read surface with matching asset key to be added to hash maps.
** If surface->filename == NULL, free(surface->pixels); free(surface);
** Increment offset.
*/

static t_scene	*read_surface(t_doom3d *app,
					t_file_contents *file, int32_t *offset)
{
	t_surface	*surface;
	uint32_t	*pixels;
	uint32_t	pixels_size;
	const char	filename[128];
	uint32_t	len;

	ft_memset(filename, 0, sizeof(filename));
	len = 0;
	ft_memcpy(&len, file->buf + *offset, sizeof(uint32_t));
	*offset += sizeof(uint32_t);
	ft_memcpy(filename, file->buf + *offset, len);
	*offset += len;
	error_check(!(surface = ft_calloc(sizeof(t_surface))),
		"Failed to alloc surface");
	ft_memcpy(&surface, file->buf + *offset, sizeof(t_surface));
	*offset += sizeof(t_surface);
	pixels_size = sizeof(uint32_t) * surface->w * surface->h;
	error_check(!(pixels = ft_calloc(pixels_size)), "Failed to allc pixels");
	surface->pixels = pixels;
	*offset += pixels_size;
	surface->filename = get_matching_asset_key(app, filename);
	return (surface);
}

static uint32_t	read_and_add_surface_asset(t_doom3d *app, t_hash_table *asset_map,
					t_file_contents *file, int32_t offset)
{
	t_surface	*surface;
	t_surface	*existing_surface;

	surface = read_surface(app, file, &offset);
	if (surface->filename == NULL)
	{
		free(surface->pixels);
		free(surface);
	}
	else
	{
		existing_surface = hash_map_get(asset_map, (int64_t)surface->filename);
		if (existing_surface != NULL)
		{
			free(existing_surface->pixels);
			free(existing_surface);
		}
		hash_map_add(asset_map, (int64_t)surface->filename, surface);
	}
	return (offset);
}

static uint32_t	read_texture_assets_first_half(t_doom3d *app,
					t_file_contents *file, int32_t offset)
{
	int32_t	i;
	int32_t	num_written_assets;

	num_written_assets = 0;
	ft_memcpy(&num_written_assets, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	i = -1;
	while (++i < num_written_assets)
		offset = read_and_add_surface_asset(app,
			app->assets.sprite_textures, file, offset);
	ft_memcpy(&num_written_assets, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	i = -1;
	while (++i < num_written_assets)
		offset = read_and_add_surface_asset(app,
			app->assets.hud_textures, file, offset);
	return (offset);	
}

uint32_t	read_texture_assets(t_doom3d *app,
				t_file_contents *file, int32_t offset)
{
	int32_t	i;
	int32_t	num_written_assets;

	num_written_assets = 0;
	offset = read_texture_assets_first_half(app, file, offset);
	ft_memcpy(&num_written_assets, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	i = -1;
	while (++i < num_written_assets)
		offset = read_and_add_surface_asset(app,
			app->assets.textures, file, offset);
	ft_memcpy(&num_written_assets, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	i = -1;
	while (++i < num_written_assets)
		offset = read_and_add_surface_asset(app,
			app->assets.normal_maps, file, offset);
	return (offset);
}
