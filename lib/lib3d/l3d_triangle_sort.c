/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:49:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/28 17:56:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Triangle sorting implemented with
** https://developer.nvidia.com/blog/
** thinking-parallel-part-iii-tree-construction-gpu/
*/

/*
** Expands a 10-bit integer into 30 bits
** by inserting 2 zeros after each bit.
*/

static unsigned int		expand_bits(unsigned int v)
{
	v = (v * 0x00010001u) & 0xFF0000FFu;
	v = (v * 0x00000101u) & 0x0F00F00Fu;
	v = (v * 0x00000011u) & 0xC30C30C3u;
	v = (v * 0x00000005u) & 0x49249249u;
	return v;
}

/*
** Calculates a 30-bit Morton code for the
** given 3D point located within the unit cube [0,1].
*/

static unsigned int		morton_3d(t_vec3 normalized_pos)
{
	float	x;
	float	y;
	float	z;

	x = fmin(fmax(normalized_pos[0] * 1024.0f, 0.0f), 1023.0f);
	y = fmin(fmax(normalized_pos[1] * 1024.0f, 0.0f), 1023.0f);
	z = fmin(fmax(normalized_pos[2] * 1024.0f, 0.0f), 1023.0f);
	return (expand_bits((unsigned int)x) * 4 +
		expand_bits((unsigned int)y) * 2 +
		expand_bits((unsigned int)z));
}

static t_box3d			triangle_bounding_box(t_triangle *triangle)
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

/*
** Sort triangle vector by morton codes as keys, indices as values.
** Use temp array to place triangles in right order back to the vector.
** Start and end offsets are used to leave space for triangles that are not
** part of sorting.
*/

void					triangle_sort_by_morton_code(t_tri_vec *triangles,
							t_thread_pool *pool, uint32_t start,
							uint32_t end)
{
	uint32_t	i;
	t_triangle	*tmp[end - start];
	uint32_t	morton_codes[end - start];
	uint32_t	triangle_indices[end - start];
	t_box3d		aabb;

	i = -1;
	while (++i < end - start)
	{
		tmp[i] = triangles->triangles[start + i];
		aabb = triangle_bounding_box(triangles->triangles[start + i]);
		ml_vector3_normalize(aabb.center, aabb.center);
		morton_codes[i] = morton_3d(aabb.center);
		triangle_indices[i] = i;
	}
	radix_sort_key_val(pool, (uint32_t*[2]){morton_codes, triangle_indices},
		end - start);
	i = -1;
	while (++i < end - start)
		triangles->triangles[start + i] = tmp[triangle_indices[i]];
}