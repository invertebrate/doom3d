/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:00:21 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 17:40:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# ifdef __APPLE__
#  include <SDL.h>
# endif
# ifdef __linux__
#  include <SDL2/SDL.h>
# endif

# include "libft.h"
# include "sound.h"
# include "animations_3d.h"

# define MAX_ASSETS 512
# define GAME_FONT "assets/fonts/AmazDooMLeft.ttf"
# define DEBUG_FONT "assets/fonts/Roboto-Regular.ttf"

/*
** Sound files in sound.h
*/

# define MONSTER01_MODEL "assets/models/monster_01/monster01_basemodel_000.obj"
# define MONSTER01_TEXTURE "assets/textures/monster_01/monster01_diffuse.bmp"
# define MONSTER01A_TEXTURE "assets/textures/monster_01/monster01a_diffuse.bmp"
# define MONSTER01B_TEXTURE "assets/textures/monster_01/monster01b_diffuse.bmp"
# define MONSTER01_NORMM "assets/textures/monster_01/monster01_normal.bmp"
# define MONSTER02_MODEL "assets/models/monster_02/monster02_basemodel_000.obj"
# define MONSTER02_TEXTURE "assets/textures/monster_02/monster02_diffuse.bmp"
# define MONSTER02_NORMM "assets/textures/monster_02/monster02_normal.bmp"
# define NPC_ELEVATOR_MODEL "assets/models/box.obj"
# define NPC_ELEVATOR_TEXTURE "assets/textures/rock.bmp"
# define NPC_ELEVATOR_NORMM "assets/textures/rock.bmp"
# define ELEVATOR_SWITCH_TEXTURE "assets/textures/lava.bmp"
# define NPC_PROJECTILE_00 "assets/textures/npc_projectile_texture.bmp"
# define NPC_PROJECTILE_01 "assets/textures/npc_projectile_texture_green.bmp"
# define NPC_PROJECTILE_02 "assets/textures/npc_projectile_texture_purple.bmp"

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

typedef struct s_sized_file
{
	void	*data;
	size_t	size;
}			t_sized_file;

typedef struct s_assets
{
	t_sized_file			sounds[SOUNDS_NUM_TRACKS];
	t_sized_file			main_font;
	t_sized_file			small_font;
	t_sized_file			title_font;
	t_asset_files			asset_files;
	t_hash_table			*models;
	t_hash_table			*animation_3d_frames;
	t_hash_table			*hud_textures;
	t_hash_table			*sprite_textures;
	t_hash_table			*textures;
	t_hash_table			*normal_maps;
	t_hash_table			*npc_map;
	t_hash_table			*prefab_map;
	t_hash_table			*trigger_map;
	t_hash_table			*lights_map;
	t_surface				*skybox_textures[6];
}				t_assets;

#endif