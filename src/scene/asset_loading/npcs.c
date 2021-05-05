/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:41:18 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:12:44 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	weird_npcs_load(t_scene *scene)
{
	scene->asset_files.npc_names[scene->asset_files.num_npcs]
		= "Elevator Platform";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
		(void *)npc_type_elevator);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] = "Crate";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
		(void *)npc_type_crate);
}

void	npcs_load(t_scene *scene)
{
	scene->npc_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] = "Monster01";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
		(void *)npc_type_monster01);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] = "Monster01 A";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
		(void *)npc_type_monster01_a);
	scene->asset_files.npc_names[scene->asset_files.num_npcs]
		= "Monster01 range";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
		(void *)npc_type_monster01_range);
	scene->asset_files.npc_names[scene->asset_files.num_npcs]
		= "Monster02 range";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
		(void *)npc_type_monster02);
	weird_npcs_load(scene);
}
