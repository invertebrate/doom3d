/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triggers_drops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:30:06 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/30 21:30:08 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	weapon_drops_load(t_scene *scene)
{
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Shotgun Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_weapon_drop_shotgun);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Pistol Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_weapon_drop_pistol);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"RPG Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_weapon_drop_rpg);
}

void	item_drops_load(t_scene *scene)
{
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Jetpack Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_item_jetpack);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Medkit Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_item_medkit);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Key Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_item_key);
}
