/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 19:04:19 by ohakola          ###   ########.fr       */
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
		"Monster01";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
			(void*)npc_type_monster01);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] =
		"Monster01 A";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
			(void*)npc_type_monster01_a);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] =
		"Monster01 range";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
			(void*)npc_type_monster01_range);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] =
		"Monster02 range";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
			(void*)npc_type_monster02);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] =
		"Elevator Platform";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
			(void*)npc_type_elevator);
	scene->asset_files.npc_names[scene->asset_files.num_npcs] =
		"Crate";
	hash_map_add(scene->npc_map,
		(int64_t)scene->asset_files.npc_names[scene->asset_files.num_npcs++],
			(void*)npc_type_crate);
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
		"Pistol Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_weapon_drop_pistol);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"RPG Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_weapon_drop_rpg);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Jetpack Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_item_jetpack);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Medkit Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_item_medkit);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Key Drop";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_item_key);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Door/Elevator Switch";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_elevator_switch);
	scene->asset_files.trigger_names[scene->asset_files.num_triggers] =
		"Door/Elevator Timer Switch";
	hash_map_add(scene->trigger_map,
		(int64_t)scene->asset_files.trigger_names[
			scene->asset_files.num_triggers++],
			(void*)trigger_door_switch);
}

static void		lights_load(t_scene *scene)
{
	scene->lights_map = hash_map_create(MAX_ASSETS);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Normal Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_yellow);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Red Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_red);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Green Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_green);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Blue Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_blue);
	scene->asset_files.light_names[scene->asset_files.num_lights] =
		"Cyan Light";
	hash_map_add(scene->trigger_map, (int64_t)scene->asset_files.light_names[
			scene->asset_files.num_lights++], (void*)light_type_cyan);
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
		"assets/textures/rock.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/crate.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_dirt.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal_2048.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal2_2048.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal3.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal4.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_metal4_box.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/door_metal_h.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/door_metal_v.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/wall_metal_panel.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/floor_redsand.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/shotgun_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/pistol_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/rpg_texture.bmp";
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
	data->texture_files[data->num_textures++] =
		NPC_MONSTER01_TEXTURE;
	data->texture_files[data->num_textures++] =
		NPC_MONSTER01A_TEXTURE;
	data->texture_files[data->num_textures++] =
		NPC_MONSTER01B_TEXTURE;
	data->texture_files[data->num_textures++] =
		"assets/textures/monster_02/monster02_diffuse.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/npc_projectile_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_corner_floor.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_corner_inner.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_corner_outer.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_straight_floor.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_straight_wall.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_t_floor.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/corridor_x_floor.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/keypad_texture.bmp";
	data->texture_files[data->num_textures++] =
		"assets/textures/medkit_texture.bmp";
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
	assets_load(scene, &scene->asset_files);
	prefabs_load(scene);
	npcs_load(scene);
	triggers_load(scene);
	lights_load(scene);
}
