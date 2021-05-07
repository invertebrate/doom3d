/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_sort_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 00:16:48 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/07 23:12:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Normalize a position inside a bounded world box between 0 and 1
*/

void	normalize_by_world_box(t_vec3 position,
			t_box3d *world_box)
{
	int32_t		i;

	i = -1;
	while (++i < 3)
	{
		position[i] = (position[i] - world_box->xyz_min[i])
			/ (world_box->xyz_max[i] - world_box->xyz_min[i]);
	}
}

/*
** Return triangle's bounding box (axis aligned bounding box)
*/

t_box3d	l3d_triangle_bounding_box(t_triangle *triangle)
{
	int32_t	i;
	t_box3d	aabb;
	t_vec3	half_size;

	i = -1;
	while (++i < 3)
	{
		aabb.xyz_min[i] = fmin(fmin(triangle->vtc[0]->pos[i],
					triangle->vtc[1]->pos[i]), triangle->vtc[2]->pos[i]);
		aabb.xyz_max[i] = fmax(fmax(triangle->vtc[0]->pos[i],
					triangle->vtc[1]->pos[i]), triangle->vtc[2]->pos[i]);
	}
	ml_vector3_sub(aabb.xyz_max, aabb.xyz_min, aabb.size);
	ml_vector3_mul(aabb.size, 0.5, half_size);
	ml_vector3_add(aabb.xyz_min, half_size, aabb.center);
	aabb.is_collider = false;
	return (aabb);
}

void	triangle_sort_free(t_triangle **tmp, uint32_t *keys,
				uint32_t *indices)
{
	free(tmp);
	free(keys);
	free(indices);
}

uint32_t	get_padded_size(uint32_t size)
{
	if (size % EXPECTED_THREADS == 0)
		return (size);
	return (size + EXPECTED_THREADS - (size % EXPECTED_THREADS));
}

void	reorder_sorted_triangles(t_tri_vec *triangles, t_triangle **tmp,
			uint32_t *key_vals[2])
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)triangles->size)
		triangles->triangles[i] = tmp[key_vals[1][i]];
}
