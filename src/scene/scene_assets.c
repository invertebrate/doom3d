/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/28 19:32:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		scene_set_skybox_textures(t_scene *scene)
{
	scene->skybox_textures[0] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/front.bmp");
	scene->skybox_textures[1] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/left.bmp");
	scene->skybox_textures[2] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/top.bmp");
	scene->skybox_textures[3] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/back.bmp");
	scene->skybox_textures[4] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/right.bmp");
	scene->skybox_textures[5] = l3d_read_bmp_32bit_rgba_surface(
		"assets/skybox/bottom.bmp");
}

/*
** Loads assets by keys and files set in scene_data.c
** Hashmap = dictionary
*/

static void		assets_load(t_scene *scene, t_asset_files *data)
{
	int32_t		i;

	scene->models = hash_map_create(MAX_ASSETS);
	scene->textures = hash_map_create(MAX_ASSETS);
	scene->normal_maps = hash_map_create(MAX_ASSETS);
	i = -1;
	while (++i < (int32_t)data->num_models)
		hash_map_add(scene->models,
			(int64_t)scene->asset_files.model_files[i],
			l3d_read_obj(scene->asset_files.model_files[i], NULL, NULL));
	i = -1;
	while (++i < (int32_t)data->num_textures)
		hash_map_add(scene->textures,
			(int64_t)scene->asset_files.texture_files[i],
			l3d_read_bmp_32bit_rgba_surface(
				scene->asset_files.texture_files[i]));
	i = -1;
	while (++i < (int32_t)data->num_normal_maps)
		hash_map_add(scene->normal_maps,
			(int64_t)scene->asset_files.normal_map_files[i],
			l3d_read_bmp_32bit_rgba_surface(
				scene->asset_files.normal_map_files[i]));
	scene_set_skybox_textures(scene);
}

static void		scene_texture_files_set(t_asset_files *data)
{
	data->texture_files[data->num_textures++] =
		"assets/textures/lava.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/Dirs.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/rock.bmp";
}

static void		scene_normal_files_set(t_asset_files *data)
{
	data->normal_map_files[data->num_normal_maps++] =
		"assets/textures/lava_normal.bmp";
}

static void		scene_model_files_set(t_asset_files *data)
{
	data->model_files[data->num_models++] =
		"assets/models/box.obj";
}

/*
** Load all imported assets here, rest should be done with the editor.
*/

void			scene_assets_load(t_scene *scene)
{
	scene->asset_files.num_models = 0;
	scene->asset_files.num_textures = 0;
	scene->asset_files.num_normal_maps = 0;
	scene_texture_files_set(&scene->asset_files);
	scene_normal_files_set(&scene->asset_files);
	scene_model_files_set(&scene->asset_files);
	assets_load(scene, &scene->asset_files);
}
