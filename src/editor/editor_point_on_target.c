/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_point_on_target.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 01:22:17 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 01:22:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Find an offset that is half of the bounding box and return that to be applied
** for placement. (t_vec3){0.02, 0.02, 0.02} is a small vector added to aabb
** size for the case of e.g. planes (0 width)
*/

static void		editor_point_on_target_offset(t_doom3d *app,
					t_vec3 target_point, t_vec3 normal, t_vec3 offset)
{
	t_ray			ray;
	t_hits			*hits;
	t_hit			*closest;
	t_box3d			aabb;

	ml_vector3_copy(target_point, aabb.center);
	ml_vector3_copy(app->editor.selected_objects[0]->aabb.size, aabb.size);
	ml_vector3_add(aabb.size, (t_vec3){0.02, 0.02, 0.02}, aabb.size);
	ml_vector3_mul(aabb.size, 0.5, aabb.size);
	ml_vector3_add(aabb.center, aabb.size, aabb.xyz_max);
	ml_vector3_sub(aabb.center, aabb.size, aabb.xyz_min);
	ml_vector3_mul(aabb.size, 1.0, aabb.size);
	ml_vector3_normalize(normal, ray.dir);
	ml_vector3_copy((t_vec3){
		1.0 / ray.dir[0], 1.0 / ray.dir[1], 1.0 / ray.dir[2]}, ray.dir_inv);
	ml_vector3_copy(target_point, ray.origin);
	hits = NULL;
	closest = NULL;
	if (l3d_bounding_box_ray_hit(&aabb, &ray, &hits, true))
	{
		l3d_get_closest_hit(hits, &closest);
		if (closest != NULL)
			ml_vector3_sub(target_point, closest->hit_point, offset);
		l3d_delete_hits(&hits);
	}
}

/*
** Returns hit point by mouse, but ignores the currently selected one,
** Useful when e.g. placing a new object.
*/

void			editor_point_on_target(t_doom3d *app,
					t_vec3 result)
{
	t_vec3			mouse_world_pos;
	t_vec3			dir;
	t_hits			*hits;
	t_hit			*closest_triangle_hit;
	t_vec3			add;

	if (app->editor.num_selected_objects == 0)
		return ;
	hits = NULL;
	get_mouse_world_position(app, mouse_world_pos);
	ml_vector3_sub(mouse_world_pos, app->player.pos, dir);
	ml_vector3_normalize(dir, dir);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.pos,
		dir, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_triangle_hit,
			app->editor.selected_objects[0]->id);
		if (closest_triangle_hit != NULL)
		{
			editor_point_on_target_offset(app, closest_triangle_hit->hit_point,
				closest_triangle_hit->normal, add);
			ml_vector3_add(closest_triangle_hit->hit_point, add, result);
		}
		l3d_delete_hits(&hits);
	}
}
