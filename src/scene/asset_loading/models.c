/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   models.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:58:39 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/27 01:56:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		scene_model_files_set_sub(t_asset_files *data)
{
	data->model_files[data->num_models++] =
		"assets/models/corridor_corner_floor.obj";
	data->model_files[data->num_models++] =
		"assets/models/corridor_corner_inner.obj";
	data->model_files[data->num_models++] =
		"assets/models/corridor_corner_outer.obj";
	data->model_files[data->num_models++] =
		"assets/models/corridor_straight_floor.obj";
	data->model_files[data->num_models++] =
		"assets/models/corridor_straight_wall.obj";
	data->model_files[data->num_models++] =
		"assets/models/corridor_t_floor.obj";
	data->model_files[data->num_models++] =
		"assets/models/corridor_x_floor.obj";
	data->model_files[data->num_models++] = "assets/models/keypad.obj";
	data->model_files[data->num_models++] = "assets/models/jetpack.obj";
	data->model_files[data->num_models++] = "assets/models/medkit.obj";
	data->model_files[data->num_models++] = "assets/models/light_sphere.obj";
}

void			scene_model_files_set(t_asset_files *data)
{
	data->model_files[data->num_models++] = "assets/models/box.obj";
	data->model_files[data->num_models++] =
		"assets/models/monster_01/monster01_basemodel_000.obj";
	data->model_files[data->num_models++] =
		"assets/models/monster_02/monster02_basemodel_000.obj";
	data->model_files[data->num_models++] = "assets/models/shotgun.obj";
	data->model_files[data->num_models++] = "assets/models/pistol.obj";
	data->model_files[data->num_models++] = "assets/models/rpg.obj";
	data->model_files[data->num_models++] = "assets/models/missile.obj";
	data->model_files[data->num_models++] = "assets/models/npc_projectile.obj";
	data->model_files[data->num_models++] =
		"assets/models/window/window_glass.obj";
	data->model_files[data->num_models++] =
		"assets/models/window/window_wall.obj";
	scene_model_files_set_sub(data);
}
