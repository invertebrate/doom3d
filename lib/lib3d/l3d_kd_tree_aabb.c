/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_kd_tree_aabb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:49:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Initializes bounding box before finding min maxes (or nulls it if triangle
** size is 0)
*/

static void			init_bounding_box(t_box3d *res, t_tri_vec *triangles)
{
	ml_vector3_copy((t_vec3){INT32_MIN, INT32_MIN, INT32_MIN}, res->xyz_max);
	ml_vector3_copy((t_vec3){INT32_MAX, INT32_MAX, INT32_MAX}, res->xyz_min);
	if (triangles->size == 0)
	{
		ft_memset(res->xyz_min, 0, sizeof(t_vec3));
		ft_memset(res->xyz_max, 0, sizeof(t_vec3));
		ft_memset(res->center, 0, sizeof(t_vec3));
		ft_memset(res->size, 0, sizeof(t_vec3));
	}
}

/*
** Sets bounding box's size and center
*/

static void			bounding_box_size_and_center_set(t_box3d *res)
{
	ml_vector3_copy((t_vec3){res->xyz_max[0] - res->xyz_min[0],
		res->xyz_max[1] - res->xyz_min[1],
		res->xyz_max[2] - res->xyz_min[2],
	}, res->size);
	ml_vector3_copy((t_vec3){res->xyz_min[0] + res->size[0] / 2.,
		res->xyz_min[1] + res->size[1] / 2.,
		res->xyz_min[2] + res->size[2] / 2.,
	}, res->center);
}

/*
** Sets bounding box of triangle vector (list of triangles) by finding
** max xyzs and min xyzs
*/

void				l3d_bounding_box_set(t_tri_vec *triangles, t_box3d *res)
{
	int		i;
	int		j;
	float	min;
	float	max;

	init_bounding_box(res, triangles);
	i = -1;
	while (++i < (int)triangles->size)
	{
		j = -1;
		while (++j < 3)
		{
			min = l3d_fmin(triangles->triangles[i]->vtc[0]->pos[j], l3d_fmin(
				triangles->triangles[i]->vtc[1]->pos[j],
				triangles->triangles[i]->vtc[2]->pos[j]));
			res->xyz_min[j] = res->xyz_min[j] < min ? res->xyz_min[j] : min;
			max = l3d_fmax(triangles->triangles[i]->vtc[0]->pos[j], l3d_fmax(
				triangles->triangles[i]->vtc[1]->pos[j],
				triangles->triangles[i]->vtc[2]->pos[j]));
			res->xyz_max[j] = res->xyz_max[j] > max ? res->xyz_max[j] : max;
		}
	}
	bounding_box_size_and_center_set(res);
}

/*
** Returns the longes axis of a bounding box.
*/

t_axis				l3d_bounding_box_longest_axis(t_box3d bounding_box)
{
	float	longest;
	int		i;

	longest = l3d_fmax(bounding_box.size[0],
		l3d_fmax(bounding_box.size[1], bounding_box.size[2]));
	i = -1;
	while (++i < 3)
		if (bounding_box.size[i] == longest)
			break ;
	return (i);
}
