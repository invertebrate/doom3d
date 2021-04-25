/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:45:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 19:45:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			lights_load(t_scene *scene)
{
	scene->lights_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Normal Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_yellow);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Red Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_red);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Green Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_green);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Blue Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_blue);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Cyan Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_cyan);
}
