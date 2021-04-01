/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:49:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/02 00:18:08 by ohakola          ###   ########.fr       */
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
	return (v);
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

t_box3d					triangle_bounding_box(t_triangle *triangle)
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

void					normalize_by_world_box(t_vec3 position,
							t_box3d *world_box)
{
	int32_t		i;

	i = -1;
	while (++i < 3)
	{
		position[i] = (position[i] - world_box->xyz_min[i]) /
			(world_box->xyz_max[i] - world_box->xyz_min[i]);
	}
}

/*
** Sort triangle vector by morton codes as keys, indices as values.
** Use temp array to place triangles in right order back to the vector.
** Sorts relative to world box
*/

void					triangle_sort_by_morton_code(t_tri_vec *triangles,
							t_thread_pool *pool, t_box3d *world_box)
{
	uint32_t	i;
	t_triangle	*tmp[triangles->size];
	uint32_t	morton_codes[triangles->size];
	uint32_t	triangle_indices[triangles->size];
	t_box3d		aabb;

	i = -1;
	while (++i < triangles->size)
	{
		tmp[i] = triangles->triangles[i];
		aabb = triangle_bounding_box(triangles->triangles[i]);
		normalize_by_world_box(aabb.center, world_box);
		morton_codes[i] = morton_3d(aabb.center);
		triangle_indices[i] = i;
	}
	radix_sort_key_val(pool, (uint32_t*[2]){morton_codes, triangle_indices},
		triangles->size);
	i = -1;
	while (++i < triangles->size)
		triangles->triangles[i] = tmp[triangle_indices[i]];
}
