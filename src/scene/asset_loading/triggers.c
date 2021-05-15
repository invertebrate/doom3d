/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:44:56 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 17:51:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	level_end_start_load(t_scene *scene)
{
	scene->asset_files.trigger_names[scene->asset_files.num_triggers]
		= "Level Start";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
		scene->asset_files.num_triggers++],
		(void *)trigger_player_start);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers]
		= "Level End";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
		scene->asset_files.num_triggers++],
		(void *)trigger_player_end);
}

static void	switches_load(t_scene *scene)
{
	scene->asset_files.trigger_names[scene->asset_files.num_triggers]
		= "Door/Elevator Switch";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
		scene->asset_files.num_triggers++],
		(void *)trigger_elevator_switch);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers]
		= "Door/Elevator Timer Switch";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
		scene->asset_files.num_triggers++],
		(void *)trigger_door_switch);
}

static void	hurtbox_load(t_scene *scene)
{
	scene->asset_files.trigger_names[scene->asset_files.num_triggers]
		= "Hurtbox";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
		scene->asset_files.num_triggers++],
		(void *)trigger_hurtbox);
}

static void	soundbox_load(t_scene *scene)
{
	scene->asset_files.trigger_names[scene->asset_files.num_triggers]
		= "Jukebox";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
		scene->asset_files.num_triggers++],
		(void *)trigger_jukebox);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers]
		= "Musicbox";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
		scene->asset_files.num_triggers++],
		(void *)trigger_musicbox);
}

void	triggers_load(t_scene *scene)
{
	level_end_start_load(scene);
	weapon_drops_load(scene);
	item_drops_load(scene);
	switches_load(scene);
	hurtbox_load(scene);
	soundbox_load(scene);
}
