/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:05:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:44:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	set_aabb_origin_to_corners(t_3d_object *obj,
				t_vec3 origin, t_vec3 origin_to_corner[8])
{
	ml_vector3_sub(origin, obj->aabb.xyz_min, origin_to_corner[0]);
	ml_vector3_sub(origin, obj->aabb.xyz_max, origin_to_corner[1]);
	ml_vector3_sub(origin, (t_vec3){obj->aabb.xyz_max[0], obj->aabb.xyz_min[1],
		obj->aabb.xyz_min[2]}, origin_to_corner[2]);
	ml_vector3_sub(origin, (t_vec3){obj->aabb.xyz_min[0], obj->aabb.xyz_max[1],
		obj->aabb.xyz_max[2]}, origin_to_corner[3]);
	ml_vector3_sub(origin, (t_vec3){obj->aabb.xyz_min[0], obj->aabb.xyz_min[1],
		obj->aabb.xyz_max[2]}, origin_to_corner[4]);
	ml_vector3_sub(origin, (t_vec3){obj->aabb.xyz_max[0], obj->aabb.xyz_max[1],
		obj->aabb.xyz_min[2]}, origin_to_corner[5]);
	ml_vector3_sub(origin, (t_vec3){obj->aabb.xyz_max[0], obj->aabb.xyz_min[1],
		obj->aabb.xyz_max[2]}, origin_to_corner[6]);
	ml_vector3_sub(origin, (t_vec3){obj->aabb.xyz_min[0], obj->aabb.xyz_max[1],
		obj->aabb.xyz_min[2]}, origin_to_corner[7]);
}

t_bool	object_too_far(t_doom3d *app, t_3d_object *obj)
{
	float		too_far;
	t_vec3		player_to_obj;

	if (app->active_scene->scene_id == scene_id_main_game)
		too_far = app->unit_size * GAME_VIEW_DIST_UNITS;
	else
		too_far = app->unit_size * EDITOR_VIEW_DIST_UNITS;
	ml_vector3_sub(obj->position, app->player.pos,
		player_to_obj);
	if (ml_vector3_mag(player_to_obj) > too_far)
		return (true);
	return (false);
}

/*
** Sets z value for triangle vertices. Unit size division is used to bring
** the number to a more reasonable range - to be more standard for rasterizer
** and e.g. depth shading.
*/

void	update_triangle_vertex_zvalues(t_triangle *triangle,
			float unit_size)
{
	triangle->vtc_zvalue[0] = 1.0
		/ (triangle->vtc[0]->pos[2] / unit_size + L3D_EPSILON);
	triangle->vtc_zvalue[1] = 1.0
		/ (triangle->vtc[1]->pos[2] / unit_size + L3D_EPSILON);
	triangle->vtc_zvalue[2] = 1.0
		/ (triangle->vtc[2]->pos[2] / unit_size + L3D_EPSILON);
}
