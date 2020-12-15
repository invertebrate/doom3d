/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_asset_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/15 19:08:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		scene_texture_files_set(t_scene_data *data)
{
	data->texture_files[0] = "assets/textures/lava.bmp";
}

static void		scene_normal_files_set(t_scene_data *data)
{
	data->normal_map_files[0] = "assets/textures/lava_normal.bmp";
}

static void		scene_model_files_set(t_scene_data *data)
{
	data->model_files[0] = "assets/models/axismodels.obj";
}

void			main_scene_data_asset_files_set(t_scene_data *data)
{
	data->asset_keys[0] = 0x0;
	data->num_assets_to_load = 1;
	scene_texture_files_set(data);
	scene_normal_files_set(data);
	scene_model_files_set(data);
}
