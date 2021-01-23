/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/23 16:48:23 by ohakola          ###   ########.fr       */
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

static void		model_animation_frames_load(t_scene *scene, t_asset_files *data)
{
	int		i;

	scene->model_anim_frames = hash_map_create(MAX_ASSETS);
	i = -1;
	while (++i < (int32_t)data->num_model_animation_frames)
		hash_map_add(scene->model_anim_frames,
			(int64_t)scene->asset_files.model_animation_files[i],
			l3d_read_obj(scene->asset_files.model_animation_files[i],
				NULL, NULL));
}

/*
** Loads assets by keys and files set in scene_data.c
** Hashmap = dictionary
*/

static void		assets_load(t_scene *scene, t_asset_files *data)
{
	int32_t		i;
	t_surface	*animation_source;
	t_surface	*scaled_anim_source;

	scene->models = hash_map_create(MAX_ASSETS);
	scene->textures = hash_map_create(MAX_ASSETS);
	scene->normal_maps = hash_map_create(MAX_ASSETS);
	scene->animation_textures = hash_map_create(MAX_ASSETS);
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
	model_animation_frames_load(scene, data);
	i = -1;
	while (++i < (int32_t)data->num_sprite_animations)
	{
		animation_source = l3d_read_bmp_32bit_rgba_surface(
				scene->asset_files.sprite_animation_files[i]);
		scaled_anim_source = l3d_image_scaled(animation_source,
			animation_source->w * ANIMATION_SCALE, animation_source->h *
				ANIMATION_SCALE);
		free(animation_source->pixels);
		free(animation_source);
		hash_map_add(scene->animation_textures,
			(int64_t)scene->asset_files.sprite_animation_files[i],
			scaled_anim_source);
	}
	scene_set_skybox_textures(scene);
}

static void		npcs_load(t_scene *scene)
{
	scene->npc_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] =
		"Default Enemy";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
			(void*)npc_type_default);
}

static void		prefabs_load(t_scene *scene)
{
	scene->prefab_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.prefab_names[scene->asset_files.num_npcs] =
		"Plane";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[
			scene->asset_files.num_prefabs++],
			(void*)prefab_plane);
}

static void		triggers_load(t_scene *scene)
{
	scene->trigger_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Level Start";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_player_start);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Level End";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_player_end);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Shotgun Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_weapon_drop_shotgun);
}

/*
** Set animation file paths (and they also work as keys when queried from
** hash_table)
*/

static void		scene_sprite_animation_files_set(t_asset_files *data)
{
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/shotgun_anim_1080p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/pistol_anim_1080p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/fist_anim_1080p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/rpg_anim_1080p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/shotgun_anim_720p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/pistol_anim_720p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/fist_anim_720p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/rpg_anim_720p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/shotgun_anim_540p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/pistol_anim_540p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/fist_anim_540p.bmp";
	data->sprite_animation_files[data->num_sprite_animations++] =
		"assets/animations/rpg_anim_540p.bmp";
}

static void		scene_texture_files_set(t_asset_files *data)
{
	data->texture_files[data->num_textures++] =
		"assets/textures/lava.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/Dirs.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/rock.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/shotgun_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/explosion1.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/explosion2.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/explosion3.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/explosion4.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/blood.bmp";
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
		"assets/models/missile.obj";
	data->model_files[data->num_models++] =
		"assets/models/run_frame.obj";
}

static void		scene_model_animation_files_set(t_asset_files *data,
					char* file_path, uint32_t framecount)
{
	int		i;
	char	*frame_path;
	
	i = -1;
	while(++i < (int)framecount && i < 100)
	{
		error_check(!(frame_path =
			(char*)ft_calloc(sizeof(char) * ft_strlen(file_path) + 4)),
			"Failed to malloc file path for animation");
		if (i < 10)
		{
			ft_sprintf(frame_path, "%s_00%d.obj", file_path, i);
		}
		else if (i > 10 && i < 100)
		{
			ft_sprintf(frame_path, "%s_0%d.obj	", file_path, i);
		}
		data->sprite_animation_files[data->num_model_animation_frames++] =
			frame_path;
	}
}

/*
** Load all imported assets here, rest should be done with the editor.
*/

void			scene_assets_load(t_scene *scene)
{
	scene->asset_files.num_models = 0;
	scene->asset_files.num_textures = 0;
	scene->asset_files.num_normal_maps = 0;
	scene->asset_files.num_npcs = 0;
	scene->asset_files.num_prefabs = 0;
	scene->asset_files.num_sprite_animations = 0;
	scene_texture_files_set(&scene->asset_files);
	scene_normal_files_set(&scene->asset_files);
	scene_model_files_set(&scene->asset_files);
	if (scene->scene_id == scene_id_main_game)
	{
		scene_model_animation_files_set(&scene->asset_files,
			"assets/models/run_frame", 6);
		scene_sprite_animation_files_set(&scene->asset_files);
	}
	assets_load(scene, &scene->asset_files);
	prefabs_load(scene);
	npcs_load(scene);
	triggers_load(scene);
}
