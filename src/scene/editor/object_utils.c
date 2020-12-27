/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:36:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/27 15:58:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Place object whose assets exist in memory (obj, texture & normal maps
** have been read into scene)
*/

void		place_object(t_doom3d *app, const char *filenames[3],
				t_vec3 pos)
{
	t_3d_object	*obj;
	t_3d_object	*model;
	t_surface	*texture;
	t_surface	*normal_map;

	model = hash_map_get(app->active_scene->models, (int64_t)filenames[0]);
	if (!model)
	{
		ft_dprintf(2, "No existing model file (%s) given to place object. "
			"Add it in scene_assets.c\n",
			filenames[0]);
		return ;
	}
	obj = l3d_object_instantiate(model, app->unit_size, false);
	texture = hash_map_get(app->active_scene->textures, (int64_t)filenames[1]);
	if (texture)
	{
		l3d_object_set_texture(obj, texture);
		hash_map_add(app->active_scene->object_textures, obj->id,
			(void*)filenames[1]);
	}
	normal_map = hash_map_get(app->active_scene->textures,
		(int64_t)filenames[2]);
	if (normal_map)
	{
		l3d_object_set_normal_map(obj, normal_map);
		hash_map_add(app->active_scene->object_normal_maps,
			obj->id, (void*)filenames[2]);
	}
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	app->active_scene->objects[app->active_scene->num_objects++] = obj;
}

/*
** Place object from model (add textures from memory)
*/

void		place_procedural_object(t_doom3d *app, t_3d_object *model,
				const char *filenames[2], t_vec3 pos)
{
	t_3d_object	*obj;
	t_surface	*texture;
	t_surface	*normal_map;

	if (!model)
	{
		ft_dprintf(2, "No existing model object (NULL) given\n");
		return ;
	}
	obj = l3d_object_instantiate(model, app->unit_size, false);
	texture = hash_map_get(app->active_scene->textures, (int64_t)filenames[0]);
	if (texture)
	{
		l3d_object_set_texture(obj, texture);
		hash_map_add(app->active_scene->object_textures, obj->id,
			(void*)filenames[0]);
	}
	normal_map = hash_map_get(app->active_scene->textures,
		(int64_t)filenames[1]);
	if (normal_map)
	{
		l3d_object_set_normal_map(obj, normal_map);
		hash_map_add(app->active_scene->object_normal_maps,
			obj->id, (void*)filenames[1]);
	}
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	app->active_scene->objects[app->active_scene->num_objects++] = obj;
}
