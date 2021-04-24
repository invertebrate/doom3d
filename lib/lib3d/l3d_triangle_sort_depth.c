/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_sort_depth.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 00:16:48 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:45:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Sorts triangles by their depth value inside world box centered in origin
** Assumes thus that triangles are viewed from 0, 0, 0.
*/

void					triangle_sort_by_depth(t_tri_vec *triangles,
							t_thread_pool *pool, t_box3d *world_box)
{
	uint32_t	i;
	t_triangle	*tmp[triangles->size];
	uint32_t	depths[triangles->size];
	uint32_t	triangle_indices[triangles->size];
	t_vec3		center;

	i = -1;
	while (++i < triangles->size)
	{
		tmp[i] = triangles->triangles[i];
		ml_vector3_copy(triangles->triangles[i]->center, center);
		normalize_by_world_box(center, world_box);
		depths[i] = (uint32_t)(center[2] * 10000000.0f);
		triangle_indices[i] = i;
	}
	radix_sort_key_val(pool, (uint32_t*[2]){depths, triangle_indices},
		triangles->size);
	i = -1;
	while (++i < triangles->size)
		triangles->triangles[i] = tmp[triangle_indices[i]];
}
