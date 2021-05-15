/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:41:18 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 20:39:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	weird_npcs_load(t_assets *assets)
{
	assets->asset_files.npc_names[assets->asset_files.num_npcs]
		= "Elevator Platform";
	hash_map_add(assets->npc_map,
		(int64_t)assets->asset_files.npc_names[assets->asset_files.num_npcs++],
		(void *)npc_type_elevator);
	assets->asset_files.npc_names[assets->asset_files.num_npcs] = "Crate";
	hash_map_add(assets->npc_map,
		(int64_t)assets->asset_files.npc_names[assets->asset_files.num_npcs++],
		(void *)npc_type_crate);
	assets->asset_files.npc_names[assets->asset_files.num_npcs] = "Boss";
	hash_map_add(assets->npc_map,
		(int64_t)assets->asset_files.npc_names[assets->asset_files.num_npcs++],
		(void *)npc_type_boss);
}

void	npcs_load(t_assets *assets)
{
	assets->asset_files.npc_names[assets->asset_files.num_npcs] = "Monster01";
	hash_map_add(assets->npc_map,
		(int64_t)assets->asset_files.npc_names[assets->asset_files.num_npcs++],
		(void *)npc_type_monster01);
	assets->asset_files.npc_names[assets->asset_files.num_npcs] = "Monster01 A";
	hash_map_add(assets->npc_map,
		(int64_t)assets->asset_files.npc_names[assets->asset_files.num_npcs++],
		(void *)npc_type_monster01_a);
	assets->asset_files.npc_names[assets->asset_files.num_npcs]
		= "Monster01 range";
	hash_map_add(assets->npc_map,
		(int64_t)assets->asset_files.npc_names[assets->asset_files.num_npcs++],
		(void *)npc_type_monster01_range);
	assets->asset_files.npc_names[assets->asset_files.num_npcs]
		= "Monster02 range";
	hash_map_add(assets->npc_map,
		(int64_t)assets->asset_files.npc_names[assets->asset_files.num_npcs++],
		(void *)npc_type_monster02);
	weird_npcs_load(assets);
}
