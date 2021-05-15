/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 18:26:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	create_asset_memory_maps(t_scene *scene)
{
	scene->models = hash_map_create(MAX_ASSETS);
	scene->textures = hash_map_create(MAX_ASSETS);
	scene->normal_maps = hash_map_create(MAX_ASSETS);
	scene->animation_3d_frames = hash_map_create(ANIM_3D_FRAME_MAX);
	if (scene->scene_id == scene_id_editor3d)
	{
		scene->prefab_map = hash_map_create(MAX_ASSETS);
		scene->npc_map = hash_map_create(MAX_ASSETS);
		scene->trigger_map = hash_map_create(MAX_ASSETS);
		scene->lights_map = hash_map_create(MAX_ASSETS);
	}
	if (scene->scene_id == scene_id_main_game)
	{
		scene->hud_textures = hash_map_create(MAX_ASSETS);
		scene->sprite_textures = hash_map_create(MAX_ASSETS);
	}
}

static void	load_models_textures_and_nmaps_to_memory(t_scene *scene,
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

static void	set_scene_asset_files_to_load(t_scene *scene)
{
	scene->asset_files.num_models = 0;
	scene->asset_files.num_textures = 0;
	scene->asset_files.num_normal_maps = 0;
	scene->asset_files.num_npcs = 0;
	scene->asset_files.num_prefabs = 0;
	scene->asset_files.num_triggers = 0;
	scene->asset_files.num_lights = 0;
	scene->asset_files.num_hud_textures = 0;
	scene->asset_files.num_animation_frames_3d = 0;
	scene->asset_files.num_sprites = 0;
	scene_texture_files_set(&scene->asset_files);
	scene_normal_map_files_set(&scene->asset_files);
	scene_model_files_set(&scene->asset_files);
	scene_animation_3d_files_set(&scene->asset_files);
	if (scene->scene_id == scene_id_main_game)
	{
		scene_animation_sprite_files_set(&scene->asset_files);
		scene_hud_icon_files_set(&scene->asset_files);
	}
}

/*
** Load all imported assets here, rest should be done with the editor.
*/

void	scene_assets_load(t_scene *scene)
{
	set_scene_asset_files_to_load(scene);
	create_asset_memory_maps(scene);
	if (scene->scene_id == scene_id_main_game)
	{
		load_skybox_textures_to_memory(scene);
		load_sprites_to_memory(scene, &scene->asset_files);
		load_hud_textures_to_memory(scene, &scene->asset_files);
	}
	if (scene->scene_id == scene_id_editor3d)
	{
		prefabs_load(scene);
		npcs_load(scene);
		triggers_load(scene);
		lights_load(scene);
	}
	load_animation_3d_frames_to_memory(scene, &scene->asset_files);
	load_models_textures_and_nmaps_to_memory(scene, &scene->asset_files);
}
