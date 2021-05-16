/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 20:23:59 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 20:47:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static size_t	get_3d_obj_size(t_3d_object *obj)
{
	size_t	size_count;

	size_count = 0;
	size_count += obj->num_vertices * sizeof(t_vertex);
	size_count += obj->num_triangles * sizeof(t_triangle);
	size_count += sizeof(t_material);
	size_count += sizeof(t_3d_object);
	return (size_count);
}

static void	add_surface_size(int64_t key, void *val, void *params)
{
	t_surface	*surface;
	size_t		*counter;

	counter = params;
	surface = val;
	*counter += sizeof(uint32_t);
	*counter += ft_strlen((char*)key);
	*counter += sizeof(t_surface);
	*counter += sizeof(uint32_t) * surface->w * surface->h;
}

static void	add_3d_animation_frame_size(int64_t key, void *val, void *params)
{
	t_3d_object	*obj;
	size_t		*counter;

	counter = params;
	obj = val;
	*counter += sizeof(uint32_t);
	*counter += ft_strlen((char*)key);
	*counter += get_3d_obj_size(obj);
}

static size_t	get_sdl_asset_size(SDL_RWops *asset)
{
	return (asset->size(asset));
}

size_t	get_assets_write_size(t_assets *assets)
{
	size_t	size_count;
	int32_t	i;

	size_count = 0;
	i = -1;
	while (++i < 6)
		add_surface_size(i, assets->skybox_textures[i], &size_count);
	hash_map_foreach(assets->sprite_textures, add_surface_size, &size_count);
	hash_map_foreach(assets->hud_textures, add_surface_size, &size_count);
	hash_map_foreach(assets->textures, add_surface_size, &size_count);
	hash_map_foreach(assets->normal_maps, add_surface_size, &size_count);
	hash_map_foreach(assets->animation_3d_frames,
		add_3d_animation_frame_size, &size_count);
	i = -1;
	while (++i < SOUNDS_NUM_TRACKS)
		size_count += get_sdl_asset_size(assets->sounds[i]);
	size_count += get_sdl_asset_size(assets->main_font);
	size_count += get_sdl_asset_size(assets->title_font);
	size_count += get_sdl_asset_size(assets->small_font);
	return (size_count);
}
