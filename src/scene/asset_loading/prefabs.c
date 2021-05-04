/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefabs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:48:35 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:22:31 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	prefabs_load(t_scene *scene)
{
	scene->prefab_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.prefab_names[scene->asset_files.num_prefabs] = "Plane";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[
		scene->asset_files.num_prefabs++], (void *)prefab_plane);
	scene->asset_files.prefab_names[scene->asset_files.num_prefabs]
		= "Window Wall";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[
		scene->asset_files.num_prefabs++], (void *)prefab_window_wall);
	scene->asset_files.prefab_names[scene->asset_files.num_prefabs]
		= "Path Node";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[
		scene->asset_files.num_prefabs++], (void *)prefab_path_node);
	scene->asset_files.prefab_names[scene->asset_files.num_prefabs]
		= "Lava plane";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[
		scene->asset_files.num_prefabs++], (void *)prefab_lava_plane);
}
