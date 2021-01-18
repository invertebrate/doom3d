/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_grounded.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:15:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/18 22:42:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_3d_object	*object_under(t_doom3d *app,
					t_vec3 origin, uint32_t self_id)
{
	t_hits		*hits;
	t_hit		*closest_hit;
	t_3d_object	*hit_parent;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		(t_vec3){0, Y_DIR, 0}, &hits))
	{
		l3d_get_closest_hit(hits, &closest_hit, self_id);
		if (!closest_hit)
			return (NULL);
		hit_parent = closest_hit->triangle->parent;
		l3d_delete_hits(&hits);
		return (hit_parent);
	}
	return (NULL);
}

static t_3d_object	*object_under_aabb(t_doom3d *app, t_box3d *aabb,
						uint32_t ignore_id)
{
	t_vec3		origin;
	t_3d_object	*obj_under;

	ml_vector3_copy(
		(t_vec3){aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_min[2]}, origin);
	ml_vector3_copy(
		(t_vec3){aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_max[2]}, origin);
	if ((obj_under = object_under(app, origin, ignore_id)))
		return (obj_under);
	ml_vector3_copy(
		(t_vec3){aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_max[2]}, origin);
	if ((obj_under = object_under(app, origin, ignore_id)))
		return (obj_under);
	ml_vector3_copy(
		(t_vec3){aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_min[2]}, origin);
	if ((obj_under = object_under(app, origin, ignore_id)))
		return (obj_under);
	ml_vector3_copy(
		(t_vec3){aabb->center[0], aabb->center[1] + aabb->size[1] / 2.0,
			aabb->center[2]}, origin);
	if ((obj_under = object_under(app, origin, ignore_id)))
		return (obj_under);
	return (NULL);
}

/*
** 1. Check objects exist under by casting rays from corners and bottom center
** of aabb.
** 2. If object under exists, check it collides with self aabb.
*/

t_bool	obj_is_grounded(t_doom3d *app, t_3d_object *falling_obj)
{
	t_3d_object	*obj_under;

	obj_under = object_under_aabb(app, &falling_obj->aabb, falling_obj->id);
	if (obj_under)
		return (l3d_aabb_collides(&obj_under->aabb, &falling_obj->aabb));
	return (false);
}

/*
** 1. Check objects exist under by casting rays from corners and bottom center
** of aabb.
** 2. If object under exists, check it collides with self aabb.
*/

t_bool	player_is_grounded(t_doom3d *app)
{
	t_3d_object	*obj_under;

	obj_under = object_under_aabb(app, &app->player.aabb, -1);
	if (obj_under)
		return (l3d_aabb_collides(&obj_under->aabb, &app->player.aabb));
	return (false);
}