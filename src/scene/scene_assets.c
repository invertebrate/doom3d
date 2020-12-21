/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/21 20:00:26 by ohakola          ###   ########.fr       */
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
	uint32_t	key;

	scene->models = hash_map_create(MAX_ASSETS);
	scene->textures = hash_map_create(MAX_ASSETS);
	scene->normal_maps = hash_map_create(MAX_ASSETS);
	i = -1;
	while (++i < (int32_t)data->num_keys)
	{
		key = data->asset_keys[i];
		if (hash_map_get(scene->asset_files.texture_files, key) != NULL)
			hash_map_add(scene->textures, key,
				l3d_read_bmp_32bit_rgba_surface(
					hash_map_get(scene->asset_files.texture_files, key)));
		if (hash_map_get(scene->asset_files.normal_map_files, key) != NULL)
			hash_map_add(scene->normal_maps, key,
				l3d_read_bmp_32bit_rgba_surface(
					hash_map_get(scene->asset_files.normal_map_files, key)));
		if (hash_map_get(scene->asset_files.model_files, key) != NULL)
		{
			hash_map_add(scene->models, key,
				l3d_read_obj(
					hash_map_get(scene->asset_files.model_files, key),
					hash_map_get(scene->textures, key),
					hash_map_get(scene->normal_maps, key)));
		}
	}
	scene_set_skybox_textures(scene);
}

static void		add_asset_file(t_asset_files *data,
					t_hash_table *table, int32_t key, char *filename)
{
	hash_map_add(table, key, filename);
	data->loaded_filenames[data->num_files++] = filename;
}

static void		scene_texture_files_set(t_asset_files *data)
{
	add_asset_file(data, data->texture_files, 0,
		"assets/textures/lava.bmp");
}

static void		scene_normal_files_set(t_asset_files *data)
{
	add_asset_file(data, data->normal_map_files, 0,
		"assets/textures/lava_normal.bmp");
}

static void		scene_model_files_set(t_asset_files *data)
{
	add_asset_file(data, data->model_files, 0,
		"assets/models/axismodels.obj");
}

void			scene_assets_load(t_scene *scene)
{
	scene->asset_files.model_files = hash_map_create(MAX_ASSETS);
	scene->asset_files.texture_files = hash_map_create(MAX_ASSETS);
	scene->asset_files.normal_map_files = hash_map_create(MAX_ASSETS);
	scene->asset_files.asset_keys[0] = 1;
	scene->asset_files.num_keys = 1;
	scene->asset_files.num_files = 0;
	scene_texture_files_set(&scene->asset_files);
	scene_normal_files_set(&scene->asset_files);
	scene_model_files_set(&scene->asset_files);
	assets_load(scene, &scene->asset_files);
}
