/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:36:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/12 21:47:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

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
*/

static uint32_t	next_object_index(t_doom3d *app)
{
	uint32_t	next_index;

	if (app->active_scene->num_deleted > 0)
	{
		next_index = app->active_scene->deleted_object_i[
			app->active_scene->num_deleted - 1];
		app->active_scene->num_deleted--;
		app->active_scene->num_objects++;
		return (next_index);
	}
	next_index = app->active_scene->num_objects++;
	return (next_index);
}

void			object_set_for_deletion(t_doom3d *app, t_3d_object *object)
{
	int32_t		i;
	uint32_t	del_index;
	int32_t		sum;

	i = -1;
	sum = (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted);
	while (++i < sum)
	{
		if (app->active_scene->objects[i] != NULL &&
			app->active_scene->objects[i]->id == object->id)
		{
			app->active_scene->num_deleted++;
			app->active_scene->num_objects--;
			del_index = app->active_scene->num_deleted - 1;
			app->active_scene->deleted_object_i[del_index] = i;
			break ;
		}
	}
}

/*
** Place object whose assets exist in memory (obj, texture & normal maps
** have been read into scene)
*/

void			place_scene_object(t_doom3d *app, const char *filenames[3],
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
}

/*
** Place object from model (add textures from memory)
*/

void			place_procedural_scene_object(t_doom3d *app, t_3d_object *model,
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
	else if (obj->type == object_type_item)
		ft_sprintf(str, "%s", "Item");
}