/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forces_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <veilo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:43:15 by veilo             #+#    #+#             */
/*   Updated: 2021/04/30 13:50:12 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object			*object_under(t_doom3d *app,
					t_vec3 origin, uint32_t self_id, t_vec3 hit_point)
{
	t_hits		*hits;
	t_hit		*closest_hit;
	t_3d_object	*hit_parent;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		(t_vec3){0, Y_DIR, 0}, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_hit, self_id);
		if (!closest_hit)
		{
			l3d_delete_hits(&hits);
			return (NULL);
		}
		hit_parent = closest_hit->triangle->parent;
		ml_vector3_copy(closest_hit->hit_point, hit_point);
		l3d_delete_hits(&hits);
		return (hit_parent);
	}
	return (NULL);
}

t_3d_object			*object_above(t_doom3d *app,
					t_vec3 origin, uint32_t self_id, t_vec3 hit_point)
{
	t_hits		*hits;
	t_hit		*closest_hit;
	t_3d_object	*hit_parent;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		(t_vec3){0, -Y_DIR, 0}, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_hit, self_id);
		if (!closest_hit)
		{
			l3d_delete_hits(&hits);
			return (NULL);
		}
		hit_parent = closest_hit->triangle->parent;
		ml_vector3_copy(closest_hit->hit_point, hit_point);
		l3d_delete_hits(&hits);
		return (hit_parent);
	}
	return (NULL);
}

/*
** 1. Check objects exist under by casting rays from corners and bottom center
** of aabb.
** 2. If object under exists, check it collides with self aabb.
*/

t_bool				obj_is_grounded(t_doom3d *app, t_3d_object *falling_obj)
{
	t_3d_object	*obj_under;
	t_vec3		origin;
	t_vec3		hit_point;
	t_bool		ret;

	ret = false;
	ml_vector3_copy((t_vec3){falling_obj->aabb.center[0],
				falling_obj->aabb.center[1] + falling_obj->aabb.size[1] / 2.0,
				falling_obj->aabb.center[2]}, origin);
	obj_under = object_under(app, origin, falling_obj->id, hit_point);
	if (obj_under)
	{
		if (hit_point[1] <= origin[1] &&
			hit_point[1] >= origin[1] - falling_obj->aabb.size[1] * 1.5 &&
						obj_under->type != object_type_projectile &&
						obj_under->type != object_type_npc)
			ret = true;
	}
	return (ret);
}
