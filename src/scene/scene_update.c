/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:43:52 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/17 01:37:36 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Objects defined here will not be included in triangle tree.
** Such objects should not be part ray-cast interaction in game.
** Objects too far will not be part of the tree as well. Because they also
** won't be rendered or part of physics then.
*/

static t_bool	include_object_in_triangle_tree(t_doom3d *app,
							t_3d_object *object)
{
	if (!object)
		return (false);
	if (object->type == object_type_npc
		&& ((t_npc*)object->params)->state == state_death_anim)
		return (false);
	if (object_is_ignored(app, object))
		return (false);
	if (app->active_scene->scene_id == scene_id_editor3d)
		return (true);
	if (object->params_type == light_type_breakable)
		return (true);
	return (object->type != object_type_light
		&& object->type != object_type_path
		&& !(object->type == object_type_trigger
			&& (object->params_type == trigger_player_start
				|| object->params_type == trigger_player_end
				|| object->params_type == trigger_hurtbox
				|| object->params_type == trigger_jukebox
				|| object->params_type == trigger_musicbox)));
}

/*
** Sets active scene's triangle refs (pointers to scene triangles which are
** used in triangle tree for collision and raycast detection)
** This should be updated once per frame
*/

static void	active_scene_triangle_refs_set(t_doom3d *app)
{
	int32_t		i;
	int32_t		j;
	int32_t		k;
	t_scene		*scene;

	scene = app->active_scene;
	if (app->active_scene->triangle_ref != NULL)
		free(app->active_scene->triangle_ref);
	i = -1;
	scene->num_triangles = 0;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
		if (include_object_in_triangle_tree(app, scene->objects[i]))
			scene->num_triangles += scene->objects[i]->num_triangles;
	error_check(!(scene->triangle_ref = ft_calloc(sizeof(t_triangle *)
				* scene->num_triangles)), "Failed to malloc triangle ref");
	i = -1;
	k = 0;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (!include_object_in_triangle_tree(app, scene->objects[i]))
			continue ;
		j = -1;
		while (++j < scene->objects[i]->num_triangles)
			scene->triangle_ref[k++] = &scene->objects[i]->triangles[j];
	}
}

static void	update_temp_object_light_sources(t_scene *scene)
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

void	active_scene_update_after_objects(t_doom3d *app)
{
	int32_t	i;
	t_scene	*scene;

	scene = app->active_scene;
	scene->num_scene_lights = 0;
	update_temp_object_light_sources(scene);
	i = -1;
	while (++i < (int32_t)(scene->num_objects + scene->num_deleted))
	{
		if (scene->objects[i])
		{
			if (object_is_ignored(app, scene->objects[i]))
				continue ;
			l3d_object_aabb_update(scene->objects[i]);
			if (scene->objects[i]->type == object_type_light
				|| scene->objects[i]->type == object_type_projectile)
				scene->scene_lights[scene->num_scene_lights++]
					= scene->objects[i];
		}
	}
	active_scene_triangle_refs_set(app);
	l3d_kd_tree_create_or_update(&scene->triangle_tree,
		scene->triangle_ref, scene->num_triangles);
}
