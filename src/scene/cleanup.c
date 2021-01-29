/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/29 20:44:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		scene_textures_destroy(t_scene *scene)
{
	t_surface	*texture;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)scene->asset_files.num_textures)
	{
		if ((texture = hash_map_get(scene->textures,
				(int64_t)scene->asset_files.texture_files[i])))
			free(texture->pixels);
	}
	hash_map_destroy_free(scene->textures);
	hash_map_destroy(scene->object_textures);
	i = -1;
	while (++i < (int32_t)scene->asset_files.num_animations_sprite)
	{
		if ((texture = hash_map_get(scene->animation_textures,
				(int64_t)scene->asset_files.animation_sprite_files[i])))
			free(texture->pixels);
	}
	hash_map_destroy_free(scene->animation_textures);
}

void		scene_normal_maps_destroy(t_scene *scene)
{
	t_surface	*normal_map;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)scene->asset_files.num_normal_maps)
	{
		if ((normal_map = hash_map_get(scene->normal_maps,
			(int64_t)scene->asset_files.normal_map_files[i])))
			free(normal_map->pixels);
	}
	hash_map_destroy_free(scene->normal_maps);
	hash_map_destroy(scene->object_normal_maps);
}

void		scene_assets_destroy(t_scene *scene)
{
	t_3d_object	*model;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)scene->asset_files.num_models)
		if ((model = hash_map_get(scene->models,
			(int64_t)scene->asset_files.model_files[i])))
			l3d_3d_object_destroy(model);
	hash_map_destroy(scene->models);
	hash_map_destroy(scene->npc_map);
	hash_map_destroy(scene->prefab_map);
	hash_map_destroy(scene->trigger_map);
	i = -1;
	while (++i < (int32_t)scene->asset_files.num_animations_3d)
	{
		if ((model = hash_map_get(scene->animation_3d_frames,
				(int64_t)scene->asset_files.animation_3d_files[i])))
			l3d_3d_object_destroy(model);
		free((void*)scene->asset_files.animation_3d_files[i]);
	}
	hash_map_destroy(scene->animation_3d_frames);
}

void		scene_skybox_destroy(t_scene *scene)
{
	int32_t		i;

	i = -1;
	while (++i < 6)
	{
		l3d_3d_object_destroy(scene->skybox[i]);
		free(scene->skybox_textures[i]->pixels);
		free(scene->skybox_textures[i]);
	}
}

static void	npc_destroy(t_animation_3d *npc_obj)
{
		/*typedef struct				s_animation_3d
	{
		uint32_t				frame_count;
		uint32_t				current_frame;
		uint32_t				start_frame;
		uint32_t				start_tick;
		t_3d_object				*base_object;
		t_3d_object				**animation_frames; //contains the objects for each anim frame
		int32_t					*anim_frame_numbers; //contains the frame indices for each animation start
	}							t_animation_3d;
	//ToDo: Move this function under npc_destroy.c
	//Loop through animations under NPC and call l3d_3d_object_destroy on
	//the frames
	//then free t_animation_3d
	//then l3d_3d_object_destroy on npc_obj
	*/
	(void)npc_obj;
}

void		scene_objects_destroy(t_scene *scene)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (scene->objects[i] != NULL)
		{
			if (scene->objects[i]->type == object_type_npc)
				npc_destroy(((t_npc*)scene->objects[i]->params)->animation_3d);
			else
				l3d_3d_object_destroy(scene->objects[i]);
		}
	}
	l3d_temp_objects_destroy(&scene->temp_objects);
}


// scene->asset_files.num_anim_frames
//cleanup frames function
