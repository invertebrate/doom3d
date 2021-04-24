/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:36:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 16:08:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object		*find_object_by_id(t_doom3d *app, uint32_t id)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->id == id)
			return (app->active_scene->objects[i]);
	}
	return (NULL);
}

t_3d_object		*find_one_object_by_type(t_doom3d *app, uint32_t object_type,
					uint32_t param_type)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type &&
			app->active_scene->objects[i]->params_type == param_type)
			return (app->active_scene->objects[i]);
	}
	return (NULL);
}

/*
** // !Note that this (inc/dec)rements both num_deleted and num_objects
** so only use this when intending to actually place objects
** Saves this next index to last_object_index under scene
*/

static uint32_t	next_object_index(t_doom3d *app)
{
	uint32_t	next_index;

	if (app->active_scene->num_deleted > 0)
	{
		next_index = app->active_scene->deleted_object_i[
			app->active_scene->num_deleted - 1];
		app->active_scene->num_deleted--;
	}
	else
		next_index = app->active_scene->num_objects;
	app->active_scene->num_objects++;
	app->active_scene->last_object_index = next_index;
	return (next_index);
}

/*
** Place object whose assets exist in memory (obj, texture & normal maps
** have been read into scene)
*/

t_3d_object		*place_scene_object(t_doom3d *app, const char *filenames[3],
					t_vec3 pos)
{
	t_3d_object	*obj;
	t_3d_object	*model;
	t_surface	*texture;
	t_surface	*normal_map;

	model = hash_map_get(app->active_scene->models, (int64_t)filenames[0]);
	if (!model)
	{
		LOG_ERROR("No existing model file (%s) given to place object. "
			"Add it in scene_assets.c",
			filenames[0]);
		return (NULL);
	}
	obj = l3d_object_instantiate(model, app->unit_size);
	texture = hash_map_get(app->active_scene->textures, (int64_t)filenames[1]);
	obj->material->texture = texture;
	if (texture != NULL)
		hash_map_add(app->active_scene->object_textures, obj->id,
			(void*)filenames[1]);
	normal_map = hash_map_get(app->active_scene->textures,
		(int64_t)filenames[2]);
	obj->material->normal_map = normal_map;
	if (normal_map)
		hash_map_add(app->active_scene->object_normal_maps,
			obj->id, (void*)filenames[2]);
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	app->active_scene->objects[next_object_index(app)] = obj;
	active_scene_update_after_objects(app->active_scene);
	if (app->is_debug)
		LOG_DEBUG("New object id %d", obj->id);
	return (obj);
}

/*
** Place object from model (add textures from memory)
*/

t_3d_object		*place_procedural_scene_object(t_doom3d *app, t_3d_object *model,
					const char *filenames[2], t_vec3 pos)
{
	t_3d_object	*obj;
	t_surface	*texture;
	t_surface	*normal_map;

	if (!model)
	{
		LOG_ERROR("No existing model object (NULL) given");
		return (NULL);
	}
	obj = l3d_object_instantiate(model, app->unit_size);
	texture = hash_map_get(app->active_scene->textures, (int64_t)filenames[0]);
	obj->material->texture = texture;
	if (texture)
		hash_map_add(app->active_scene->object_textures, obj->id,
			(void*)filenames[0]);
	normal_map = hash_map_get(app->active_scene->textures,
		(int64_t)filenames[1]);
	obj->material->normal_map = normal_map;
	if (normal_map)
		hash_map_add(app->active_scene->object_normal_maps,
			obj->id, (void*)filenames[1]);
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	app->active_scene->objects[next_object_index(app)] = obj;
	active_scene_update_after_objects(app->active_scene);
	if (app->is_debug)
		LOG_DEBUG("New procedural object id %d", obj->id);
	return (obj);
}

/*
** Place object from model (add textures from memory)
*/

t_3d_object			*place_temp_object(t_doom3d *app, const char *filenames[3],
						t_vec3 pos, int32_t lifetime_and_delay[2])
{
	t_3d_object	*obj;
	t_3d_object	*model;
	t_surface	*texture;
	t_surface	*normal_map;

	model = hash_map_get(app->active_scene->models, (int64_t)filenames[0]);
	if (!model)
	{
		LOG_ERROR("No existing model file (%s) given to place object. "
			"Add it in scene_assets.c", filenames[0]);
		return (NULL);
	}
	obj = l3d_object_instantiate(model, app->unit_size);
	texture = hash_map_get(app->active_scene->textures, (int64_t)filenames[1]);
	obj->material->texture = texture;
	if (texture != NULL)
		hash_map_add(app->active_scene->object_textures, obj->id,
			(void*)filenames[1]);
	normal_map = hash_map_get(app->active_scene->textures,
		(int64_t)filenames[2]);
	obj->material->normal_map = normal_map;
	if (normal_map)
		hash_map_add(app->active_scene->object_normal_maps,
			obj->id, (void*)filenames[2]);
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	l3d_temp_objects_add(&app->active_scene->temp_objects, obj,
		lifetime_and_delay);
	if (app->is_debug)
		LOG_DEBUG("New temp object id %d", obj->id);
	return (obj);
}

/*
** Place object from model (add textures from memory)
*/

t_3d_object			*place_procedural_temp_object(t_doom3d *app,
						t_3d_object *model,
						const char *filenames[2],
						t_vec3 pos, int32_t lifetime_and_delay[2])
{
	t_3d_object	*obj;
	t_surface	*texture;
	t_surface	*normal_map;

	if (!model)
	{
		LOG_ERROR("No existing model object (NULL) given");
		return (NULL);
	}
	obj = l3d_object_instantiate(model, app->unit_size);
	texture = hash_map_get(app->active_scene->textures, (int64_t)filenames[0]);
	obj->material->texture = texture;
	if (texture)
		hash_map_add(app->active_scene->object_textures, obj->id,
			(void*)filenames[0]);
	normal_map = hash_map_get(app->active_scene->textures,
		(int64_t)filenames[1]);
	obj->material->normal_map = normal_map;
	if (normal_map)
		hash_map_add(app->active_scene->object_normal_maps,
			obj->id, (void*)filenames[1]);
	l3d_3d_object_translate(obj, pos[0], pos[1], pos[2]);
	l3d_temp_objects_add(&app->active_scene->temp_objects, obj,
		lifetime_and_delay);
	if (app->is_debug)
		LOG_DEBUG("New procedural temp object id %d", obj->id);
	return (obj);
}

void			object_type_to_str(t_3d_object *obj, char *str)
{
	if (obj->type == object_type_default)
		ft_sprintf(str, "%s", "Object");
	else if (obj->type == object_type_npc)
		ft_sprintf(str, "%s", "NPC");
	else if (obj->type == object_type_trigger)
		ft_sprintf(str, "%s", "Trigger");
	else if (obj->type == object_type_projectile)
		ft_sprintf(str, "%s", "Projectile");
	else if (obj->type == object_type_light)
		ft_sprintf(str, "%s", "Light");
	else if (obj->type == object_type_path)
		ft_sprintf(str, "%s", "Path");
}

void			extend_all_objects_shading_opts(t_doom3d *app,
					t_shading_opts opts_to_add)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
		if (app->active_scene->objects[i])
			l3d_object_set_shading_opts(app->active_scene->objects[i],
				app->active_scene->objects[i]->material->shading_opts |
					opts_to_add);
}

void			remove_all_objects_shading_opts(t_doom3d *app,
					t_shading_opts opts_to_remove)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
		if (app->active_scene->objects[i])
			l3d_object_set_shading_opts(app->active_scene->objects[i],
				app->active_scene->objects[i]->material->shading_opts ^
					opts_to_remove);
}
