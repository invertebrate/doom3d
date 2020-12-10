/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_ray_hit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:53:57 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/08 18:05:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static void		l3d_delete_hit(void *hit, size_t size)
{
	(void)size;
	if (hit != NULL)
		free(hit);
}

void			l3d_delete_hits(t_hits **hits)
{
	if (*hits == NULL)
		return ;
	ft_lstdel(hits, l3d_delete_hit);
}

void			l3d_get_closest_hit(t_hits *hits, t_hit **closest)
{
	t_hits	*head;
	t_hit	*hit;

	head = hits;
	*closest = NULL;
	while (head)
	{
		hit = (t_hit*)head->content;
		if (*closest == NULL && hit != NULL && hit->t > 0.0 && hit->triangle)
			*closest = hit;
		if (hit != NULL && hit->triangle != NULL && hit->t > 0.0 &&
			hit->t <= (*closest)->t)
			*closest = hit;
		head = head->next;
	}
	if (*closest && !(*closest)->triangle)
		*closest = NULL;
}

/*
**	Detects hit between a ray and an infinite plane in 3D. Stores the hit point
**	in a t_vec3.
*/

t_bool			l3d_plane_ray_hit(t_plane *plane, t_ray *ray,
									t_vec3 hit_point)
{
	t_vec3		temp;
	float		div;
	float		d;

	ml_vector3_sub(plane->origin, ray->origin, temp);
	if (fabs((div = ml_vector3_dot(ray->dir, plane->normal))) > L3D_EPSILON)
	{
		d = (ml_vector3_dot(temp, plane->normal)) / div;
		ml_vector3_mul(ray->dir, d, hit_point);
		ml_vector3_add(hit_point, ray->origin, hit_point);
		return (true);
	}
	return (false);
}

/*
** Fast branchless bounding box ray hit test.
** Returns true if ray hits the bounding box. If hit occurs, save distance to
** hit record's t variable (to be used in calculating hit vector).
** https://gamedev.stackexchange.com/questions/18436/
** https://tavianator.com/2011/ray_box.html
*/

t_bool			l3d_bounding_box_ray_hit(t_box3d *box, t_ray *ray,
					t_hits **hits)
{
	float	t[8];

	t[0] = (box->xyz_min[0] - ray->origin[0]) * ray->dir_inv[0];
	t[1] = (box->xyz_max[0] - ray->origin[0]) * ray->dir_inv[0];
	t[2] = (box->xyz_min[1] - ray->origin[1]) * ray->dir_inv[1];
	t[3] = (box->xyz_max[1] - ray->origin[1]) * ray->dir_inv[1];
	t[4] = (box->xyz_min[2] - ray->origin[2]) * ray->dir_inv[2];
	t[5] = (box->xyz_max[2] - ray->origin[2]) * ray->dir_inv[2];
	t[6] = l3d_fmax(l3d_fmax(l3d_fmin(t[0], t[1]), l3d_fmin(t[2], t[3])),
		l3d_fmin(t[4], t[5]));
	t[7] = l3d_fmin(l3d_fmin(l3d_fmax(t[0], t[1]), l3d_fmax(t[2], t[3])),
		l3d_fmax(t[4], t[5]));
	if (t[6] < 0 || t[6] > t[7])
		return (false);
	l3d_bounding_box_hit_record_set(t, ray, hits);
	return (true);
}
