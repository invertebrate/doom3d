/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:51:13 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	scene_textures_destroy(t_scene *scene)
{
	t_surface	*texture;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)scene->asset_files.num_textures)
	{
		texture = hash_map_get(scene->textures,
				(int64_t)scene->asset_files.texture_files[i]);
		if (texture)
			free(texture->pixels);
	}
	hash_map_destroy_free(scene->textures);
	hash_map_destroy(scene->object_textures);
	i = -1;
	while (++i < (int32_t)scene->asset_files.num_animations_sprite)
	{
		texture = hash_map_get(scene->animation_textures,
				(int64_t)scene->asset_files.animation_sprite_files[i]);
		if (texture)
			free(texture->pixels);
	}
	hash_map_destroy_free(scene->animation_textures);
}

void	scene_normal_maps_destroy(t_scene *scene)
{
	t_surface	*normal_map;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)scene->asset_files.num_normal_maps)
	{
		normal_map = hash_map_get(scene->normal_maps,
				(int64_t)scene->asset_files.normal_map_files[i]);
		if (normal_map)
			free(normal_map->pixels);
	}
	hash_map_destroy_free(scene->normal_maps);
	hash_map_destroy(scene->object_normal_maps);
}

void	scene_assets_destroy(t_scene *scene)
{
	t_3d_object	*model;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)scene->asset_files.num_models)
	{
		model = hash_map_get(scene->models,
				(int64_t)scene->asset_files.model_files[i]);
		if (model)
			l3d_3d_object_destroy(model);
	}
	hash_map_destroy(scene->models);
	hash_map_destroy(scene->npc_map);
	hash_map_destroy(scene->prefab_map);
	hash_map_destroy(scene->trigger_map);
	hash_map_destroy(scene->lights_map);
	i = -1;
	while (++i < (int32_t)scene->asset_files.num_animation_frames_3d)
	{
		model = hash_map_get(scene->animation_3d_frames,
				(int64_t)scene->asset_files.animation_3d_files[i]);
		if (model)
			l3d_3d_object_destroy(model);
		free((void *)scene->asset_files.animation_3d_files[i]);
	}
	hash_map_destroy(scene->animation_3d_frames);
}

void	scene_skybox_destroy(t_scene *scene)
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

void	scene_objects_destroy(t_scene *scene)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (scene->objects[i] != NULL)
		{
			if (scene->objects[i]->type == object_type_npc)
				npc_destroy(scene->objects[i]);
			else
				l3d_3d_object_destroy(scene->objects[i]);
		}
	}
	l3d_temp_objects_destroy(&scene->temp_objects);
}
