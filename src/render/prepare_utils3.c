/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:05:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 21:20:57 by sotamursu        ###   ########.fr       */
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
