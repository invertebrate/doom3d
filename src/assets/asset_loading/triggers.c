/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:44:56 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 20:34:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	level_end_start_load(t_assets *assets)
{
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Level Start";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_player_start);
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Level End";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_player_end);
}

static void	switches_load(t_assets *assets)
{
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Door/Elevator Switch";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_elevator_switch);
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Door/Elevator Timer Switch";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_door_switch);
}

static void	hurtbox_load(t_assets *assets)
{
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Hurtbox";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_hurtbox);
}

static void	soundbox_load(t_assets *assets)
{
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Jukebox";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_jukebox);
	assets->asset_files.trigger_names[assets->asset_files.num_triggers]
		= "Musicbox";
	hash_map_add(assets->trigger_map,
		(int64_t)assets->asset_files.trigger_names[
		assets->asset_files.num_triggers++],
		(void *)trigger_musicbox);
}

void	triggers_load(t_assets *t_assets)
{
	level_end_start_load(t_assets);
	weapon_drops_load(t_assets);
	item_drops_load(t_assets);
	switches_load(t_assets);
	hurtbox_load(t_assets);
	soundbox_load(t_assets);
}
