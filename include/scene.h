/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:14:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 17:04:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# define MAX_LIGHTS 64
# define LIGHT_INTENSITY_DEFAULT 1.5
# define LIGHT_RADIUS_DEFAULT 16.7
# define MAX_ASSETS 512
# define MAX_NUM_OBJECTS 16384
# define NEAR_CLIP_DIST 10
# define FAR_CLIP_DIST 100000

# include "libft.h"
# include "lib3d.h"
# include "window.h"
# include "animations_3d.h"

/*
** Camera defines viewbox by view planes and where screen is in the game world
** for the purpose of ray casted rendering.
*/

typedef struct				s_camera
{
	t_vec3					origin;
	float					near_clip;
	float					far_clip;
	t_plane					viewplanes[6];
	t_plane					screen;
}							t_camera;

/*
** Defines game scenes that the game contains and to which the
** app can transition while playing.
*/

typedef enum				e_scene_id
{
	scene_id_main_menu,
	scene_id_main_menu_settings,
	scene_id_main_game,
	scene_id_editor3d,
}							t_scene_id;

/*
** t_asset_files holds a list of various types of assets and their paths
** that are loaded in memory to be used in game. Each asset will correspond
** to a key in a hash map inside t_scene that are then reused by different
** game objects.
*/

typedef struct				s_asset_files
{
	const char				*animation_3d_files[ANIM_3D_FRAME_MAX];
	const char				*animation_sprite_files[MAX_ASSETS];
	const char				*texture_files[MAX_ASSETS];
	const char				*normal_map_files[MAX_ASSETS];
	const char				*model_files[MAX_ASSETS];
	const char				*npc_names[MAX_ASSETS];
	const char				*prefab_names[MAX_ASSETS];
	const char				*trigger_names[MAX_ASSETS];
	const char				*light_names[MAX_ASSETS];
	uint32_t				num_animation_frames_3d;
	uint32_t				num_animations_sprite;
	uint32_t				num_models;
	uint32_t				num_textures;
	uint32_t				num_normal_maps;
	uint32_t				num_npcs;
	uint32_t				num_prefabs;
	uint32_t				num_triggers;
	uint32_t				num_lights;
}							t_asset_files;

/*
** The main struct holding data related to the game world and their assets.
** Assets are loaded based on scene data (some of these could be under app
** to avoid reloading, but that's for a later refactor). Scene holds
** references to all objects in game (map) and their triangles (used for
** raycasting via triangle_tree).
** Scene also defines which menus each scene contains that can be interacted
** with.
** Main game will also get access to skybox via t_scene.
** All the t_hash_tables here are used for reuse of assets for game objects
** but also for mapping objects by id to their assets for map saving (e.g.
** object_textures: key: id, val: const char *filename)
*/

typedef struct				s_scene
{
	t_3d_object				*objects[MAX_NUM_OBJECTS];
	uint32_t				num_objects;
	uint32_t				deleted_object_i[MAX_NUM_OBJECTS];
	uint32_t				num_deleted;
	int32_t					last_object_index;
	t_kd_tree				*triangle_tree;
	t_triangle				**triangle_ref;
	uint32_t				num_triangles;
	t_temp_objects			*temp_objects;
	t_camera				*main_camera;
	t_camera				*third_person_camera;
	t_triangle				*screen_triangles;
	t_button_group			**menus;
	uint32_t				num_button_menus;
	t_bool					is_paused;
	t_scene_id				scene_id;
	t_hash_table			*animation_textures;
	t_hash_table			*animation_3d_frames;
	t_hash_table			*textures;
	t_hash_table			*normal_maps;
	t_hash_table			*models;
	t_hash_table			*npc_map;
	t_hash_table			*prefab_map;
	t_hash_table			*trigger_map;
	t_hash_table			*lights_map;
	t_hash_table			*object_textures;
	t_hash_table			*object_normal_maps;
	t_asset_files			asset_files;
	t_surface				*skybox_textures[6];
	t_3d_object				*skybox[6];
	uint32_t				npc_update_timer;
	t_3d_object				*scene_lights[MAX_LIGHTS];
	uint32_t				num_scene_lights;
}							t_scene;

#endif
