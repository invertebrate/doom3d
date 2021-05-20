/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers_drops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:30:06 by phakakos          #+#    #+#             */
/*   Updated: 2021/05/15 20:35:26 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	weapon_drops_load(t_assets *assets)
{
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Shotgun Drop";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_weapon_drop_shotgun);
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Pistol Drop";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_weapon_drop_pistol);
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "RPG Drop";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_weapon_drop_rpg);
}

void	item_drops_load(t_assets *assets)
{
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Jetpack Drop";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_item_jetpack);
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Medkit Drop";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_item_medkit);
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Key Drop";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_item_key);
}
