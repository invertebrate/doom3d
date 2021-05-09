/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:03:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/09 22:56:57 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	scene_normal_map_files_set2(t_asset_files *data)
{
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/rock_normal.bmp";
}

void	scene_normal_map_files_set(t_asset_files *data)
{
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/lava_normal.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/wall_metal_panel_nmm.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/crate_nmm.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/door_metal_h_nmm.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/door_metal_v_nmm.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/floor_metal3_nmm.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/floor_metal4_nmm.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/floor_metal4_box_nmm.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/monster_01/monster01_normal.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/monster_02/monster02_normal.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/alien_floor_nmm.bmp";
	data->normal_map_files[data->num_normal_maps++]
		= "assets/textures/window_wall_normal.bmp";
	scene_normal_map_files_set2(data);
}
