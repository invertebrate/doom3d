/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/08 18:05:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Set ray vectors & pre-calculate dir_inverse for faster bounding box testing.
*/

void						l3d_ray_set(t_vec3 dir, t_vec3 origin, t_ray *ray)
{
	ml_vector3_set(ray->dir, dir[0], dir[1], dir[2]);
	ml_vector3_set(ray->origin, origin[0], origin[1], origin[2]);
	ml_vector3_normalize(ray->dir, ray->dir);
	ml_vector3_set(ray->dir_inv, 1.0 / dir[0], 1.0 / dir[1], 1.0 / dir[2]);
}

void						l3d_triangle_hit_record_set(float afuvt[5],
								t_ray *ray, t_triangle *triangle, t_hits **hits)
{
	t_vec3	add;
	t_hit	hit;

	if (afuvt[4] < 0)
		return ;
	ft_memset(&hit, 0, sizeof(t_hit));
	hit.t = afuvt[4];
	hit.u = afuvt[2];
	hit.v = afuvt[3];
	ml_vector3_mul(ray->dir, hit.t, add);
	ml_vector3_add(ray->origin, add, hit.hit_point);
	ml_vector3_copy(triangle->normal, hit.normal);
	hit.triangle = triangle;
	if (*hits == NULL)
		*hits = ft_lstnew(&hit, sizeof(t_hit));
	else
		ft_lstadd(hits, ft_lstnew(&hit, sizeof(t_hit)));
}

void						l3d_bounding_box_hit_record_set(float t[8],
								t_ray *ray, t_hits **hits)
{
	t_hit	hit;
	t_vec3	add;

	ft_memset(&hit, 0, sizeof(t_hit));
	hit.t = t[6];
	ml_vector3_mul(ray->dir, hit.t, add);
	ml_vector3_add(ray->origin, add, hit.hit_point);
	if (t[6] == t[0])
		ml_vector3_copy((t_vec3){-1, 0, 0}, hit.normal);
	else if (t[6] == t[1])
		ml_vector3_copy((t_vec3){1, 0, 0}, hit.normal);
	else if (t[6] == t[2])
		ml_vector3_copy((t_vec3){0, -1, 0}, hit.normal);
	else if (t[6] == t[3])
		ml_vector3_copy((t_vec3){0, 1, 0}, hit.normal);
	else if (t[6] == t[4])
		ml_vector3_copy((t_vec3){0, 0, -1}, hit.normal);
	else if (t[6] == t[5])
		ml_vector3_copy((t_vec3){0, 0, 1}, hit.normal);
	if (*hits == NULL)
		*hits = ft_lstnew(&hit, sizeof(t_hit));
	else
		ft_lstadd(hits, ft_lstnew(&hit, sizeof(t_hit)));
}
