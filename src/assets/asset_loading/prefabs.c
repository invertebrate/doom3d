/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefabs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:48:35 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/30 20:55:11 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	prefabs_load_sub(t_assets *assets)
{
	assets->asset_files.prefab_names[assets->asset_files.num_prefabs]
		= "Reactor";
	hash_map_add(assets->prefab_map, (int64_t)assets->asset_files.prefab_names[
		assets->asset_files.num_prefabs++], (void *)prefab_reactor);
	assets->asset_files.prefab_names[assets->asset_files.num_prefabs]
		= "Hologram";
	hash_map_add(assets->prefab_map, (int64_t)assets->asset_files.prefab_names[
		assets->asset_files.num_prefabs++], (void *)prefab_hologram);
}

void	prefabs_load(t_assets *assets)
{
	assets->asset_files.prefab_names[assets->asset_files.num_prefabs] = "Plane";
	hash_map_add(assets->prefab_map,
		(int64_t)assets->asset_files.prefab_names[
		assets->asset_files.num_prefabs++], (void *)prefab_plane);
	assets->asset_files.prefab_names[assets->asset_files.num_prefabs]
		= "Window Wall";
	hash_map_add(assets->prefab_map,
		(int64_t)assets->asset_files.prefab_names[
		assets->asset_files.num_prefabs++], (void *)prefab_window_wall);
	assets->asset_files.prefab_names[assets->asset_files.num_prefabs]
		= "Path Node";
	hash_map_add(assets->prefab_map,
		(int64_t)assets->asset_files.prefab_names[
		assets->asset_files.num_prefabs++], (void *)prefab_path_node);
	assets->asset_files.prefab_names[assets->asset_files.num_prefabs]
		= "Lava plane";
	hash_map_add(assets->prefab_map,
		(int64_t)assets->asset_files.prefab_names[
		assets->asset_files.num_prefabs++], (void *)prefab_lava_plane);
	prefabs_load_sub(assets);
}
