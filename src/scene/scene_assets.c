/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:29:15 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	create_asset_memory_maps(t_scene *scene)
{
	scene->models = hash_map_create(MAX_ASSETS);
	scene->textures = hash_map_create(MAX_ASSETS);
	scene->normal_maps = hash_map_create(MAX_ASSETS);
	scene->animation_textures = hash_map_create(ANIM_3D_FRAME_MAX);
}

static void	load_models_textures_nmaps_to_memory(t_scene *scene,
					t_asset_files *data)
{
	int32_t		i;

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
}

/*
** Loads assets by keys and files
** Hashmap = dictionary
*/

static void	assets_load_to_memory(t_scene *scene, t_asset_files *data)
{
	create_asset_memory_maps(scene);
	load_models_textures_nmaps_to_memory(scene, data);
	load_animation_3d_frames_to_memory(scene, data);
	load_sprite_animations_to_memory(scene, data);
	load_skybox_textures_to_memory(scene);
}

/*
** Load all imported assets here, rest should be done with the editor.
*/

void	scene_assets_load(t_scene *scene)
{
	scene->asset_files.num_models = 0;
	scene->asset_files.num_textures = 0;
	scene->asset_files.num_normal_maps = 0;
	scene->asset_files.num_npcs = 0;
	scene->asset_files.num_prefabs = 0;
	scene->asset_files.num_animation_frames_3d = 0;
	scene->asset_files.num_animations_sprite = 0;
	scene->asset_files.num_triggers = 0;
	scene->asset_files.num_lights = 0;
	scene_texture_files_set(&scene->asset_files);
	scene_normal_map_files_set(&scene->asset_files);
	scene_model_files_set(&scene->asset_files);
	scene_animation_3d_files_set(&scene->asset_files);
	if (scene->scene_id == scene_id_main_game)
	{
		scene_animation_sprite_files_set(&scene->asset_files);
	}
	assets_load_to_memory(scene, &scene->asset_files);
	prefabs_load(scene);
	npcs_load(scene);
	triggers_load(scene);
	lights_load(scene);
}
