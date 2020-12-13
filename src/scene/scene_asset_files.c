/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_asset_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/13 20:58:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		main_scene_texture_files_set(t_scene_data *data)
{
	data->texture_files[0] = "assets/textures/Dirs.bmp";
	data->texture_files[1] = "assets/textures/lava.bmp";
}

static void		main_scene_normal_files_set(t_scene_data *data)
{
	data->normal_map_files[0] = "assets/textures/lava_normal.bmp";
	data->normal_map_files[1] = "assets/textures/lava_normal.bmp";
}

static void		main_scene_model_files_set(t_scene_data *data)
{
	data->model_files[0] = "assets/models/plane.obj";
	data->model_files[1] = "assets/models/axismodels.obj";
}

void			main_scene_data_asset_files_set(t_scene_data *data)
{
	data->asset_keys[0] = 0x0;
	data->asset_keys[1] = 0x1;
	data->num_assets_to_load = 2;
	main_scene_texture_files_set(data);
	main_scene_normal_files_set(data);
	main_scene_model_files_set(data);
}
