/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:45:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/17 18:55:55 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	lights_load2(t_scene *scene)
{
	scene->asset_files.light_names[scene->asset_files.num_lights]
		= "Cyan Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
		scene->asset_files.num_lights++], (void *)light_type_cyan);
	scene->asset_files.light_names[scene->asset_files.num_lights]
		= "Breakable Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
		scene->asset_files.num_lights++], (void *)light_type_breakable);
	scene->asset_files.light_names[scene->asset_files.num_lights]
		= "Glowing Mushroom";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
		scene->asset_files.num_lights++], (void *)light_type_mushroom);
}

void	lights_load(t_scene *scene)
{
	scene->lights_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.light_names[scene->asset_files.num_lights]
		= "White Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
		scene->asset_files.num_lights++], (void *)light_type_white);
	scene->asset_files.light_names[scene->asset_files.num_lights]
		= "Normal Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
		scene->asset_files.num_lights++], (void *)light_type_yellow);
	scene->asset_files.light_names[scene->asset_files.num_lights]
		= "Red Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
		scene->asset_files.num_lights++], (void *)light_type_red);
	scene->asset_files.light_names[scene->asset_files.num_lights]
		= "Green Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
		scene->asset_files.num_lights++], (void *)light_type_green);
	scene->asset_files.light_names[scene->asset_files.num_lights]
		= "Blue Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
		scene->asset_files.num_lights++], (void *)light_type_blue);
	lights_load2(scene);
}
