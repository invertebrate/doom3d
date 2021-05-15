/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 22:13:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	create_asset_memory_maps(t_assets *assets)
{
	assets->models = hash_map_create(MAX_ASSETS);
	assets->textures = hash_map_create(MAX_ASSETS);
	assets->normal_maps = hash_map_create(MAX_ASSETS);
	assets->animation_3d_frames = hash_map_create(ANIM_3D_FRAME_MAX);
	assets->prefab_map = hash_map_create(MAX_ASSETS);
	assets->npc_map = hash_map_create(MAX_ASSETS);
	assets->trigger_map = hash_map_create(MAX_ASSETS);
	assets->lights_map = hash_map_create(MAX_ASSETS);
	assets->hud_textures = hash_map_create(MAX_ASSETS);
	assets->sprite_textures = hash_map_create(MAX_ASSETS);
}

static void	load_models_textures_and_nmaps_to_memory(t_assets *assets,
					t_asset_files *data)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)data->num_models)
		hash_map_add(assets->models,
			(int64_t)assets->asset_files.model_files[i],
			l3d_read_obj(assets->asset_files.model_files[i], NULL, NULL));
	i = -1;
	while (++i < (int32_t)data->num_textures)
		hash_map_add(assets->textures,
			(int64_t)assets->asset_files.texture_files[i],
			l3d_read_bmp_32bit_rgba_surface(
				assets->asset_files.texture_files[i]));
	i = -1;
	while (++i < (int32_t)data->num_normal_maps)
		hash_map_add(assets->normal_maps,
			(int64_t)assets->asset_files.normal_map_files[i],
			l3d_read_bmp_32bit_rgba_surface(
				assets->asset_files.normal_map_files[i]));
}

static void	set_asset_files_to_load(t_assets *assets)
{
	assets->asset_files.num_models = 0;
	assets->asset_files.num_textures = 0;
	assets->asset_files.num_normal_maps = 0;
	assets->asset_files.num_npcs = 0;
	assets->asset_files.num_prefabs = 0;
	assets->asset_files.num_triggers = 0;
	assets->asset_files.num_lights = 0;
	assets->asset_files.num_hud_textures = 0;
	assets->asset_files.num_animation_frames_3d = 0;
	assets->asset_files.num_sprites = 0;
	texture_files_set(&assets->asset_files);
	normal_map_files_set(&assets->asset_files);
	model_files_set(&assets->asset_files);
	animation_3d_files_set(&assets->asset_files);
	sprite_animation_files_set(&assets->asset_files);
	hud_icon_files_set(&assets->asset_files);
}

/*
** Load all imported assets here, rest should be done with the editor.
** 1. Set files to load (names & keys)
** 2. Load editor related enums into assets
** 3. If asset load mode, load assets from set filenames
** 4. Otherwise load assets from first level
*/

void	doom_nukem_assets_load(t_doom3d *app)
{
	t_assets *assets;

	window_frame_clear(app->window, 0x000000ff);
	render_loading_view(app);
	draw_window_frame(app->window);
	assets = &app->assets;
	set_asset_files_to_load(assets);
	create_asset_memory_maps(assets);
	prefabs_load(assets);
	npcs_load(assets);
	triggers_load(assets);
	lights_load(assets);
	if (app->is_asset_load)
	{
		LOG_INFO("Load assets from files");
		load_skybox_textures_to_memory(assets);
		load_sprites_to_memory(assets, &assets->asset_files);
		load_hud_textures_to_memory(assets, &assets->asset_files);
		load_animation_3d_frames_to_memory(assets, &assets->asset_files);
		load_models_textures_and_nmaps_to_memory(assets, &assets->asset_files);
		sounds_load(assets);
		fonts_load(assets);
	}
	else
		load_assets_from_first_level(app);
}
