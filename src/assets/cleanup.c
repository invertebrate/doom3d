/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 21:07:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	textures_destroy(t_assets *assets)
{
	t_surface	*texture;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)assets->asset_files.num_textures)
	{
		texture = hash_map_get(assets->textures,
				(int64_t)assets->asset_files.texture_files[i]);
		if (texture)
			free(texture->pixels);
	}
	hash_map_destroy_free(assets->textures);
}

static void	normal_maps_destroy(t_assets *assets)
{
	t_surface	*normal_map;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)assets->asset_files.num_normal_maps)
	{
		normal_map = hash_map_get(assets->normal_maps,
				(int64_t)assets->asset_files.normal_map_files[i]);
		if (normal_map)
			free(normal_map->pixels);
	}
	hash_map_destroy_free(assets->normal_maps);
}

static void	model_assets_destroy(t_assets *assets)
{
	t_3d_object	*model;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)assets->asset_files.num_models)
	{
		model = hash_map_get(assets->models,
				(int64_t)assets->asset_files.model_files[i]);
		if (model)
			l3d_3d_object_destroy(model);
	}
	hash_map_destroy(assets->models);
	hash_map_destroy(assets->npc_map);
	hash_map_destroy(assets->prefab_map);
	hash_map_destroy(assets->trigger_map);
	hash_map_destroy(assets->lights_map);
}

static void	skybox_destroy(t_assets *assets)
{
	int32_t		i;

	i = -1;
	while (++i < 6)
	{
		free(assets->skybox_textures[i]->pixels);
		free(assets->skybox_textures[i]);
	}
}

void	assets_destroy(t_assets *assets)
{
	skybox_destroy(assets);
	model_assets_destroy(assets);
	normal_maps_destroy(assets);
	textures_destroy(assets);
	sprites_and_hud_destroy(assets);
	animations_3d_destroy(assets);
}