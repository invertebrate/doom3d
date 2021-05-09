/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:49:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/07 23:12:51 by ohakola          ###   ########.fr       */
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

static unsigned int	expand_bits(unsigned int v)
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

static unsigned int	morton_3d(t_vec3 normalized_pos)
{
	float	x;
	float	y;
	float	z;

	x = fmin(fmax(normalized_pos[0] * 1024.0f, 0.0f), 1023.0f);
	y = fmin(fmax(normalized_pos[1] * 1024.0f, 0.0f), 1023.0f);
	z = fmin(fmax(normalized_pos[2] * 1024.0f, 0.0f), 1023.0f);
	return (expand_bits((unsigned int)x) * 4
		+ expand_bits((unsigned int)y) * 2
		+ expand_bits((unsigned int)z));
}

static void	allocate_key_vals(uint32_t **keys, uint32_t **values,
				uint32_t padded_size)
{
	error_check(!(*keys = malloc(sizeof(uint32_t)
				* padded_size)), "Failed to allocate keys in triangle sort");
	error_check(!(*values = malloc(sizeof(uint32_t) * padded_size)),
		"Failed to allocate values in triangle sort");
}

/*
** Sort triangle vector by morton codes as keys, indices as values.
** Use temp array to place triangles in right order back to the vector.
** Sorts relative to world box
*/

void	triangle_sort_by_morton_code(t_tri_vec *triangles,
			t_thread_pool *pool, t_box3d *world_box)
{
	uint32_t	i;
	t_triangle	**tmp;
	uint32_t	*key_vals[2];
	t_box3d		aabb;
	uint32_t	padded_size;

	error_check(!(tmp = malloc(sizeof(t_triangle *) * triangles->size)), "E");
	padded_size = get_padded_size(triangles->size);
	allocate_key_vals(&key_vals[0], &key_vals[1], padded_size);
	i = -1;
	while (++i < padded_size)
	{
		if (i < triangles->size)
		{
			tmp[i] = triangles->triangles[i];
			aabb = l3d_triangle_bounding_box(triangles->triangles[i]);
			normalize_by_world_box(aabb.center, world_box);
			key_vals[0][i] = morton_3d(aabb.center);
		}
		key_vals[1][i] = i;
	}
	radix_sort_key_val(pool, key_vals, triangles->size, padded_size);
	reorder_sorted_triangles(triangles, tmp, key_vals);
	triangle_sort_free(tmp, key_vals[0], key_vals[1]);
}

/*
** Sorts triangles by their depth value inside world box centered in origin
** Assumes thus that triangles are viewed from 0, 0, 0.
*/

void	triangle_sort_by_depth(t_tri_vec *triangles,
			t_thread_pool *pool, t_box3d *world_box)
{
	uint32_t	i;
	t_triangle	**tmp;
	uint32_t	*key_vals[2];
	t_vec3		center;
	uint32_t	padded_size;

	error_check(!(tmp = malloc(sizeof(t_triangle *) * triangles->size)), "E");
	padded_size = get_padded_size(triangles->size);
	allocate_key_vals(&key_vals[0], &key_vals[1], padded_size);
	i = -1;
	while (++i < padded_size)
	{
		if (i < triangles->size)
		{
			tmp[i] = triangles->triangles[i];
			ml_vector3_copy(triangles->triangles[i]->center, center);
			normalize_by_world_box(center, world_box);
			key_vals[0][i] = (uint32_t)(center[2] * 10000000.0f);
		}
		key_vals[1][i] = i;
	}
	radix_sort_key_val(pool, key_vals, triangles->size, padded_size);
	reorder_sorted_triangles(triangles, tmp, key_vals);
	triangle_sort_free(tmp, key_vals[0], key_vals[1]);
}
