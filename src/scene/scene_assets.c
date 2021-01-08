/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/06 19:10:03 by ohakola          ###   ########.fr       */
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

static uint64_t	get_prefab_value(uint32_t object_type, uint32_t prefab_type)
{
	return (((uint64_t)object_type << 32) | (uint64_t)prefab_type);	
}

static void		prefabs_load(t_scene *scene)
{
	scene->prefab_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.prefab_names[scene->asset_files.num_prefabs] =
		"Default Enemy";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[scene->asset_files.num_prefabs],
			(void*)get_prefab_value(object_type_npc, npc_type_default));
	scene->asset_files.num_prefabs++;
	scene->asset_files.prefab_names[scene->asset_files.num_prefabs] =
		"Plane";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[scene->asset_files.num_prefabs],
			(void*)get_prefab_value(object_type_default, prefab_plane));
	scene->asset_files.num_prefabs++;
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
	data->model_files[data->num_models++] =
		"assets/models/run_frame.obj";
}

static void		animation_frames_set(t_asset_files *data, char* file_path, uint32_t framecount)
{
	int		i;
	char	*frame_path;
	
	i = -1;
	while(++i < framecount && i < 100)
	{
		frame_path = (char*)malloc(sizeof(char) * ft_strlen(file_path) + 4);
		if (i < 10)
			ft_sprintf(frame_path, "%s00%d", file_path, i);
		else if (i > 10 & i < 100)
			ft_sprintf(frame_path, "%s0%d", file_path, i);
		data->animation_files[data->num_anim_frames++] = frame_path;
	}
}

static void		scene_animation_files_set(t_asset_files *data)
{
	animation_frames_set(data, "assets/models/run_frame.obj", 6);
}

/*
** Load all imported assets here, rest should be done with the editor.
*/

void			scene_assets_load(t_scene *scene)
{
	scene->asset_files.num_models = 0;
	scene->asset_files.num_textures = 0;
	scene->asset_files.num_normal_maps = 0;
	scene->asset_files.num_prefabs = 0;
	scene_texture_files_set(&scene->asset_files);
	scene_normal_files_set(&scene->asset_files);
	scene_model_files_set(&scene->asset_files);
	scene_animation_files_set(&scene->asset_files);
	assets_load(scene, &scene->asset_files);
	prefabs_load(scene);
}
