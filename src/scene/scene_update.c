/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:43:52 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 18:51:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Objects defined here will not be included in triangle tree.
** Such objects should not be part ray-cast interaction in game.
*/

static t_bool			include_object_in_triangle_tree(t_scene *scene,
							t_3d_object *object)
{
	if (scene->scene_id == scene_id_editor3d)
		return (!!object);
	return (object != NULL &&
			object->type != object_type_light &&
			object->type != object_type_path &&
			!(object->type == object_type_trigger &&
				(object->params_type == trigger_player_start ||
					object->params_type == trigger_player_end ||
					object->params_type == trigger_hurtbox)));
}

/*
** Sets active scene's triangle refs (pointers to scene triangles which are
** used in triangle tree for collision and raycast detection)
** This should be updated once per frame
*/

static void				active_scene_triangle_refs_set(t_scene *scene)
{
	int32_t		i;
	int32_t		j;
	int32_t		k;
	int32_t		num_triangles;

	if (scene->triangle_ref != NULL)
		free(scene->triangle_ref);
	i = -1;
	num_triangles = 0;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
		if (include_object_in_triangle_tree(scene, scene->objects[i]))
			num_triangles += scene->objects[i]->num_triangles;
	scene->num_triangles = num_triangles;
	error_check(!(scene->triangle_ref = ft_calloc(sizeof(t_triangle*) *
		num_triangles)), "Failed to malloc triangle ref");
	i = -1;
	k = 0;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (!include_object_in_triangle_tree(scene, scene->objects[i]))
			continue ;
		j = -1;
		while (++j < scene->objects[i]->num_triangles)
			scene->triangle_ref[k++] = &scene->objects[i]->triangles[j];
	}
}

static void				update_temp_object_light_sources(t_scene *scene)
{
	t_temp_object			*tmp;
	t_temp_objects			*node;

	node = scene->temp_objects;
	while (node)
	{
		tmp = node->content;
		if (tmp->obj->type == object_type_light)
			scene->scene_lights[scene->num_scene_lights++] = tmp->obj;
		node = node->next;
	}
}

/*
** Update temp object light information
** Update object bounding boxes
** Update scene normal object light information
** Update triangle tree (for collisions & raycasting)
*/

void					active_scene_update_after_objects(t_scene *scene)
{
	int32_t					i;

	scene->num_scene_lights = 0;
	update_temp_object_light_sources(scene);
	i = -1;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (scene->objects[i])
		{
			l3d_object_aabb_update(scene->objects[i]);
			if (scene->objects[i]->type == object_type_light ||
				scene->objects[i]->type == object_type_projectile)
				scene->scene_lights[scene->num_scene_lights++] =
					scene->objects[i];
		}
	}
	active_scene_triangle_refs_set(scene);
	l3d_kd_tree_create_or_update(&scene->triangle_tree,
		scene->triangle_ref, scene->num_triangles);
}
