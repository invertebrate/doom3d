/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:05:31 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/10 14:21:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		set_aabb_origin_to_corners(t_3d_object *obj,
				t_vec3 origin, t_vec3 origin_to_corner[8])
{
	ml_vector3_sub(obj->aabb.xyz_min, origin, origin_to_corner[0]);
	ml_vector3_sub(obj->aabb.xyz_max, origin, origin_to_corner[1]);
	ml_vector3_sub((t_vec3){obj->aabb.xyz_max[0], obj->aabb.xyz_min[1],
		obj->aabb.xyz_min[2]}, origin, origin_to_corner[2]);
	ml_vector3_sub((t_vec3){obj->aabb.xyz_min[0], obj->aabb.xyz_max[1],
		obj->aabb.xyz_max[2]}, origin, origin_to_corner[3]);
	ml_vector3_sub((t_vec3){obj->aabb.xyz_min[0], obj->aabb.xyz_min[1],
		obj->aabb.xyz_max[2]}, origin, origin_to_corner[4]);
	ml_vector3_sub((t_vec3){obj->aabb.xyz_max[0], obj->aabb.xyz_max[1],
		obj->aabb.xyz_min[2]}, origin, origin_to_corner[5]);
	ml_vector3_sub((t_vec3){obj->aabb.xyz_max[0], obj->aabb.xyz_min[1],
		obj->aabb.xyz_max[2]}, origin, origin_to_corner[6]);
	ml_vector3_sub((t_vec3){obj->aabb.xyz_min[0], obj->aabb.xyz_max[1],
		obj->aabb.xyz_min[2]}, origin, origin_to_corner[7]);
}
