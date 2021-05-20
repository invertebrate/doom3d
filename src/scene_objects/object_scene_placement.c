/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_scene_placement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:36:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 22:22:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	set_new_object_textures_and_nmaps(t_doom3d *app,
					t_3d_object *obj,
					const char *texture_str,
					const char *normal_map_str)
{
	t_surface	*texture;
	t_surface	*normal_map;

	texture = hash_map_get(app->assets.textures, (int64_t)texture_str);
	obj->material->texture = texture;
	if (texture != NULL)
		hash_map_add(app->active_scene->object_textures,
			obj->id, (void*)texture_str);
	normal_map = hash_map_get(app->assets.textures,
			(int64_t)normal_map_str);
	obj->material->normal_map = normal_map;
	if (normal_map)
		hash_map_add(app->active_scene->object_normal_maps,
			obj->id, (void*)normal_map_str);
}

/*
** Place object whose assets exist in memory (obj, texture & normal maps
** have been read into scene)
*/

t_3d_object	*place_scene_object(t_doom3d *app, const char *filenames[3],
					t_vec3 pos)
{
	t_3d_object	*obj;
	t_3d_object	*model;

	model = hash_map_get(app->assets.models, (int64_t)filenames[0]);
	if (!model)
	{
		LOG_ERROR("No existing model file (%s) given to place object. "
			"Add it in scene_assets.c",
			filenames[0]);
		return (NULL);
	}
	obj = l3d_object_instantiate(model, app->unit_size);
	set_new_object_textures_and_nmaps(app, obj, filenames[1], filenames[2]);
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	obj->material->flashlight = &(app->player.flashlight);
	app->active_scene->objects[next_object_index(app)] = obj;
	active_scene_update_after_objects(app);
	if (app->is_debug)
		LOG_DEBUG("New object id %d", obj->id);
	return (obj);
}

/*
** Place object from model (add textures from memory)
*/

t_3d_object	*place_procedural_scene_object(t_doom3d *app,
												t_3d_object *model,
												const char *filenames[2],
												t_vec3 pos)
{
	t_3d_object	*obj;

	if (!model)
	{
		LOG_ERROR("No existing model object (NULL) given");
		return (NULL);
	}
	obj = l3d_object_instantiate(model, app->unit_size);
	set_new_object_textures_and_nmaps(app, obj, filenames[0], filenames[1]);
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	app->active_scene->objects[next_object_index(app)] = obj;
	obj->material->flashlight = &(app->player.flashlight);
	active_scene_update_after_objects(app);
	if (app->is_debug)
		LOG_DEBUG("New procedural object id %d", obj->id);
	return (obj);
}

/*
** Place object by t_3d_object *model (add textures from memory)
*/

t_3d_object	*place_procedural_temp_object(t_doom3d *app,
											t_procedural_tmp_obj_params params,
											t_vec3 pos)
{
	t_3d_object	*obj;

	if (!params.model)
	{
		LOG_ERROR("No existing model object (NULL) given");
		return (NULL);
	}
	obj = l3d_object_instantiate(params.model, app->unit_size);
	set_temp_object_sprite_texture(app, obj, params.texture);
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	l3d_temp_objects_add(&app->active_scene->temp_objects, obj,
		(int32_t[2]){params.lifetime, params.delay});
	if (app->is_debug)
		LOG_DEBUG("New procedural temp object id %d", obj->id);
	obj->material->flashlight = &(app->player.flashlight);
	return (obj);
}
