/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_asset_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/10 15:41:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		main_scene_texture_files_set(t_scene_data *data)
{
	data->texture_files[0] = "assets/textures/lava.bmp";
}

static void		main_scene_normal_files_set(t_scene_data *data)
{
	data->normal_map_files[0] = "assets/textures/lava_normal.bmp";
}

static void		main_scene_model_files_set(t_scene_data *data)
{
	data->model_files[0] = "assets/models/room_models/floor.obj";
}

void			main_scene_data_asset_files_set(t_scene_data *data)
{
	data->asset_keys[0] = 0x0;
	data->num_assets_to_load = 1;
	main_scene_texture_files_set(data);
	main_scene_normal_files_set(data);
	main_scene_model_files_set(data);
}
