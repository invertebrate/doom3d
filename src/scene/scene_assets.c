/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/16 14:29:15 by ahakanen         ###   ########.fr       */
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

static void		animation_3d_frames_load(t_scene *scene, t_asset_files *data)
{
	int		i;

	scene->animation_3d_frames = hash_map_create(ANIM_3D_FRAME_MAX);
	i = -1;
	while (++i < (int32_t)data->num_animation_frames_3d)
		hash_map_add(scene->animation_3d_frames,
			(int64_t)scene->asset_files.animation_3d_files[i],
			l3d_read_obj(scene->asset_files.animation_3d_files[i], NULL, NULL));
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
	scene->animation_textures = hash_map_create(ANIM_3D_FRAME_MAX);
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
	animation_3d_frames_load(scene, data);
	i = -1;
	while (++i < (int32_t)data->num_animations_sprite)
	{
		animation_source = l3d_read_bmp_32bit_rgba_surface(
				scene->asset_files.animation_sprite_files[i]);
		scaled_anim_source = l3d_image_scaled(animation_source,
			animation_source->w * ANIMATION_SCALE, animation_source->h *
				ANIMATION_SCALE);
		free(animation_source->pixels);
		free(animation_source);
		hash_map_add(scene->animation_textures,
			(int64_t)scene->asset_files.animation_sprite_files[i],
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
	scene->asset_files.npc_names[scene->asset_files.num_npcs] =
		"Elevator Platform";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
			(void*)npc_type_elevator);
}

static void		prefabs_load(t_scene *scene)
{
	scene->prefab_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.prefab_names[scene->asset_files.num_prefabs] =
		"Plane";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[
			scene->asset_files.num_prefabs++],
			(void*)prefab_plane);
	scene->asset_files.prefab_names[scene->asset_files.num_prefabs] =
		"Path Node";
	hash_map_add(scene->prefab_map,
		(int64_t)scene->asset_files.prefab_names[
			scene->asset_files.num_prefabs++],
			(void*)prefab_path_node);
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
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Jetpack Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_item_jetpack);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Door/Elevator Switch";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_elevator_switch);
}

/*
** Set animation file paths (and they also work as keys when queried from
** hash_table)
*/

static void		scene_animation_sprite_files_set(t_asset_files *data)
{
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/shotgun_anim_1080p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/pistol_anim_1080p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/fist_anim_1080p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/rpg_anim_1080p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/shotgun_anim_720p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/pistol_anim_720p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/fist_anim_720p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/rpg_anim_720p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/shotgun_anim_540p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/pistol_anim_540p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/fist_anim_540p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
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
	data->model_files[data->num_models++] = "assets/models/box.obj";
	data->model_files[data->num_models++] = "assets/models/monster_01/monster_01_basemodel_000.obj";
	data->model_files[data->num_models++] = "assets/models/shotgun.obj";
	data->model_files[data->num_models++] = "assets/models/missile.obj";
}

/*
**	Creates the file path for each frame in an animation clip
*/

static void		scene_animation_3d_frames_set(t_asset_files *data,
					char* file_path, uint32_t framecount)
{
	int		i;
	char	*frame_path;
	
	i = -1;
	while(++i < (int)framecount && i < 100)
	{
		frame_path = (char*)ft_calloc(sizeof(char) * ft_strlen(file_path) + 16);
		if (i < 10)
		{
			ft_sprintf(frame_path, "%s_00%d.obj", file_path, i);
		}
		else if (i >= 10 && i < 100)
		{
			ft_sprintf(frame_path, "%s_0%d.obj", file_path, i);		}
		data->animation_3d_files[data->num_animation_frames_3d++] = frame_path;
	}
}

/*
** The file path must not include the ".obj", it will be appended by
** animation_frames_set function. The function call order is important:
** each object has their animations in a contiguous chunk in the array.
*/

static void		scene_animation_3d_files_set(t_asset_files *data)
{
	scene_animation_3d_frames_set(data, "assets/models/monster_01/monster_01_basemodel", 1);
	scene_animation_3d_frames_set(data, "assets/models/monster_01/idle/monster_idle", 24);
	scene_animation_3d_frames_set(data, "assets/models/monster_01/move/monster_move", 24);
	scene_animation_3d_frames_set(data, "assets/models/monster_01/attack/monster_attack", 24);
	scene_animation_3d_frames_set(data, "assets/models/monster_01/death/monster_death", 44);
	//call the above function for each animation clip separately;
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
	scene->asset_files.num_animation_frames_3d = 0;
	scene->asset_files.num_animations_sprite = 0;
	scene_texture_files_set(&scene->asset_files);
	scene_normal_files_set(&scene->asset_files);
	scene_model_files_set(&scene->asset_files);
	scene_animation_3d_files_set(&scene->asset_files);
	if (scene->scene_id == scene_id_main_game)
	{
		scene_animation_sprite_files_set(&scene->asset_files);
	}
	assets_load(scene, &scene->asset_files);
	prefabs_load(scene);
	npcs_load(scene);
	triggers_load(scene);
}
