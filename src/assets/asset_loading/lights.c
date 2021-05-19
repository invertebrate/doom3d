/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:45:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 23:50:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	lights_load2(t_assets *assets)
{
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "Cyan Light";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_cyan);
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "Breakable Light";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_breakable);
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "Glowing Mushroom";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_mushroom);
}

void	lights_load(t_assets *assets)
{
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "White Light";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_white);
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "Normal Light";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_yellow);
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "Red Light";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_red);
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "Green Light";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_green);
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "Blue Light";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_blue);
	assets->asset_files.light_names[assets->asset_files.num_lights]
		= "Cyan Light";
	hash_map_add(assets->lights_map, (int64_t)assets->asset_files.light_names[
		assets->asset_files.num_lights++], (void *)light_type_cyan);
	lights_load2(assets);
}
