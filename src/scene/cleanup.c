/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/04 15:16:28 by ahakanen         ###   ########.fr       */
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

void		scene_models_destroy(t_scene *scene)
{
	t_3d_object	*model;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)scene->asset_files.num_models)
		if ((model = hash_map_get(scene->models,
			(int64_t)scene->asset_files.model_files[i])))
			l3d_3d_object_destroy(model);
	hash_map_destroy(scene->models);
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

void		scene_objects_destroy(t_scene *scene)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
		if (scene->objects[i] != NULL)
			l3d_3d_object_destroy(scene->objects[i]);
}
