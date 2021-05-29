/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:14:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 18:02:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# define MAX_LIGHTS 64
# define LIGHT_INTENSITY_DEFAULT 1.5
# define LIGHT_RADIUS_DEFAULT 16.7
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

typedef struct s_camera
{
	t_vec3					world_pos;
	t_vec3					forward;
	t_vec3					origin;
	float					near_clip;
	float					far_clip;
	t_plane					viewplanes[6];
	t_plane					screen;
	t_mat4					rotation;
	t_mat4					inv_rotation;
	t_mat4					translation;
	t_mat4					inv_translation;
}							t_camera;

/*
** Defines game scenes that the game contains and to which the
** app can transition while playing.
*/

typedef enum e_scene_id
{
	scene_id_main_menu,
	scene_id_main_menu_settings,
	scene_id_main_game,
	scene_id_editor3d,
}							t_scene_id;

/*
** Data for each scene view (menus, main_game, editor3d)
*/

typedef struct s_scene
{
	t_3d_object				*objects[MAX_NUM_OBJECTS];
	uint32_t				num_objects;
	uint32_t				free_object_indices[MAX_NUM_OBJECTS];
	uint32_t				num_free_indices;
	uint32_t				num_free_indices_consumed;
	int32_t					last_object_index;
	t_hash_table			*object_textures;
	t_hash_table			*object_normal_maps;
	t_kd_tree				*triangle_tree;
	t_triangle				**triangle_ref;
	uint32_t				num_triangles;
	t_temp_objects			*temp_objects;
	t_camera				*main_camera;
	t_camera				*third_person_camera;
	float					third_person_camera_distance;
	t_triangle				*screen_triangles;
	t_button_group			**menus;
	uint32_t				num_button_menus;
	t_bool					is_paused;
	t_scene_id				scene_id;
	t_3d_object				*skybox[6];
	uint32_t				npc_update_timer;
	t_3d_object				*scene_lights[MAX_LIGHTS];
	uint32_t				num_scene_lights;
}							t_scene;

#endif
