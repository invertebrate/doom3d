/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:00:21 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 20:11:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include "libft.h"
# include "animations_3d.h"

# define MAX_ASSETS 512

/*
** t_asset_files holds a list of various types of assets and their paths
** that are loaded in memory to be used in game. Each asset will correspond
** to a key in a hash map inside t_scene that are then reused by different
** game objects.
*/

typedef struct s_asset_files
{
	const char				*animation_3d_files[ANIM_3D_FRAME_MAX];
	const char				*hud_textures[MAX_ASSETS];
	const char				*sprite_files[MAX_ASSETS];
	const char				*texture_files[MAX_ASSETS];
	const char				*normal_map_files[MAX_ASSETS];
	const char				*model_files[MAX_ASSETS];
	const char				*npc_names[MAX_ASSETS];
	const char				*prefab_names[MAX_ASSETS];
	const char				*trigger_names[MAX_ASSETS];
	const char				*light_names[MAX_ASSETS];
	uint32_t				num_animation_frames_3d;
	uint32_t				num_hud_textures;
	uint32_t				num_sprites;
	uint32_t				num_models;
	uint32_t				num_textures;
	uint32_t				num_normal_maps;
	uint32_t				num_npcs;
	uint32_t				num_prefabs;
	uint32_t				num_triggers;
	uint32_t				num_lights;
}							t_asset_files;

typedef struct s_assets
{
	t_track					*library[SOUNDS];
	TTF_Font				*main_font;
	TTF_Font				*small_font;
	TTF_Font				*title_font;
	t_asset_files			asset_files;
	t_hash_table			*hud_textures;
	t_hash_table			*sprite_textures;
	t_hash_table			*animation_3d_frames;
	t_hash_table			*textures;
	t_hash_table			*normal_maps;
	t_hash_table			*models;
	t_hash_table			*npc_map;
	t_hash_table			*prefab_map;
	t_hash_table			*trigger_map;
	t_hash_table			*lights_map;
	t_surface				*skybox_textures[6];
}				t_assets;

#endif