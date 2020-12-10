/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_aabb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/08 18:06:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void				l3d_bounding_box_debug(t_box3d aabb)
{
	ft_printf("bbox.center: [%0.2f %0.2f %0.2f]\n"
		"bbox.size: [%0.2f %0.2f %0.2f]\n"
		"bbox.min_xyz: [%0.2f %0.2f %0.2f]\n"
		"bbox.max_xyz: [%0.2f %0.2f %0.2f]\n",
		aabb.center[0],
		aabb.center[1],
		aabb.center[2],
		aabb.size[0],
		aabb.size[1],
		aabb.size[2],
		aabb.xyz_min[0],
		aabb.xyz_min[1],
		aabb.xyz_min[2],
		aabb.xyz_max[0],
		aabb.xyz_max[1],
		aabb.xyz_max[2]);
}

static void			l3d_aabb_set_size_and_center(t_box3d *aabb)
{
	ml_vector3_copy((t_vec3){aabb->xyz_max[0] - aabb->xyz_min[0],
		aabb->xyz_max[1] - aabb->xyz_min[1],
		aabb->xyz_max[2] - aabb->xyz_min[2],
	}, aabb->size);
	ml_vector3_copy((t_vec3){aabb->xyz_min[0] + aabb->size[0] / 2.,
		aabb->xyz_min[1] + aabb->size[1] / 2.,
		aabb->xyz_min[2] + aabb->size[2] / 2.,
	}, aabb->center);
}

void				l3d_object_aabb_update(t_3d_object *obj)
{
	int		i;
	int		j;

	ml_vector3_copy((t_vec3){INT32_MIN, INT32_MIN, INT32_MIN},
		obj->aabb.xyz_max);
	ml_vector3_copy((t_vec3){INT32_MAX, INT32_MAX, INT32_MAX},
		obj->aabb.xyz_min);
	i = -1;
	while (++i < (int)obj->num_vertices)
	{
		j = -1;
		while (++j < 3)
		{
			obj->aabb.xyz_min[j] =
				l3d_fmin(obj->aabb.xyz_min[j], obj->vertices[i]->pos[j]);
			obj->aabb.xyz_max[j] =
				l3d_fmax(obj->aabb.xyz_max[j], obj->vertices[i]->pos[j]);
		}
	}
	l3d_aabb_set_size_and_center(&obj->aabb);
}

t_bool				l3d_aabb_collides(t_box3d *left, t_box3d *right)
{
	return ((left->xyz_min[0] < right->xyz_max[0] &&
			left->xyz_max[0] > right->xyz_min[0] &&
			left->xyz_min[1] < right->xyz_max[1] &&
			left->xyz_max[1] > right->xyz_min[1] &&
			left->xyz_min[2] < right->xyz_max[2] &&
			left->xyz_max[2] > right->xyz_min[2]));
}

t_hit				*l3d_get_aabb_hit_record(t_box3d *origin, t_box3d *target)
{
	t_vec3		dir;
	t_ray		ray;
	t_hits		*hits;
	t_hit		*hit;

	ml_vector3_sub(target->center, origin->center, dir);
	l3d_ray_set(dir, origin->center, &ray);
	hits = NULL;
	if (l3d_bounding_box_ray_hit(target, &ray, &hits))
	{
		error_check(!(hit = malloc(sizeof(t_hit))), "Failed to malloc hit");
		ft_memcpy(hit, ((t_hit*)hits->content), sizeof(t_hit));
		l3d_delete_hits(&hits);
		return (hit);
	}
	return (NULL);
}
