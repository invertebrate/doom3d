/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:49:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 00:22:24 by ohakola          ###   ########.fr       */
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
	uint32_t	*morton;
	uint32_t	*triangle_indices;
	t_box3d		aabb;

	error_check(!(tmp = malloc(sizeof(t_triangle *) * triangles->size)), "Err");
	error_check(!(morton = malloc(sizeof(uint32_t) * triangles->size)), "Err");
	error_check(!(triangle_indices = malloc(sizeof(uint32_t)
				* triangles->size)), "Err tri sort");
	i = -1;
	while (++i < triangles->size)
	{
		tmp[i] = triangles->triangles[i];
		aabb = triangle_bounding_box(triangles->triangles[i]);
		normalize_by_world_box(aabb.center, world_box);
		morton[i] = morton_3d(aabb.center);
		triangle_indices[i] = i;
	}
	radix_sort_key_val(pool, (uint32_t *[2]){morton, triangle_indices},
		triangles->size);
	i = -1;
	while (++i < triangles->size)
		triangles->triangles[i] = tmp[triangle_indices[i]];
	triangle_sort_free(tmp, morton, triangle_indices);
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
	uint32_t	*depths;
	uint32_t	*triangle_indices;
	t_vec3		center;

	error_check(!(tmp = malloc(sizeof(t_triangle *) * triangles->size)), "Err");
	error_check(!(depths = malloc(sizeof(uint32_t) * triangles->size)), "Err");
	error_check(!(triangle_indices = malloc(sizeof(uint32_t)
				* triangles->size)), "Err tri sort");
	i = -1;
	while (++i < triangles->size)
	{
		tmp[i] = triangles->triangles[i];
		ml_vector3_copy(triangles->triangles[i]->center, center);
		normalize_by_world_box(center, world_box);
		depths[i] = (uint32_t)(center[2] * 10000000.0f);
		triangle_indices[i] = i;
	}
	radix_sort_key_val(pool, (uint32_t *[2]){depths, triangle_indices},
		triangles->size);
	i = -1;
	while (++i < triangles->size)
		triangles->triangles[i] = tmp[triangle_indices[i]];
	triangle_sort_free(tmp, depths, triangle_indices);
}
