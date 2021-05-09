/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_ray_cylinder_cast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 18:22:51 by veilo             #+#    #+#             */
/*   Updated: 2021/05/09 20:05:25 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static float	get_line_angle(int index, uint32_t raycount)
{
	return (360 * ((float)index / (float)raycount));
}

static float	get_radius(uint32_t ray_count, int index, t_cylinder *cylinder)
{
	return (cylinder->radius);
	(void)ray_count;
	(void)index;
}

static void		get_ray_origin(float radius, float angle, t_vec3 origin)
{
	origin[0] = radius * cosf(angle * M_PI / 180);
	origin[2] = radius * sinf(angle * M_PI / 180);
}

static void		cast_rays_line(t_ray *rays, uint32_t ray_count, float angle,
					t_cylinder *cylinder)
{
	int		i;
	t_vec3	ray_origin;
	t_vec3	dir;

	ml_vector3_mul(cylinder->up, -1.0, dir);
	i = 0;
	while (++i < (int)ray_count)
	{
		ft_memset(ray_origin, 0, sizeof(ray_origin));
		get_ray_origin(get_radius(ray_count, i, cylinder), angle, ray_origin);
		ml_vector3_add(ray_origin, cylinder->pos, ray_origin);
		l3d_ray_set(dir, ray_origin, &(rays[i]));
	}
}

/*
** Creates rays evenly distributed in a cylindrical manner. ray_counts[0] is the
** amount of rays in a line of rays and ray_counts[1] is the number of steps when
** rotating the line of rays around.
*/

void			l3d_cast_rays_cylinder(t_ray *rays, uint32_t *ray_counts,
					t_cylinder *cylinder)
{
	int		i;
	t_vec3	down;

	i = 0;
	ml_vector3_mul(cylinder->up, -1.0, down);
	l3d_ray_set(down, cylinder->pos, &rays[0]);
	while (++i < (int)ray_counts[1])
	{
		cast_rays_line(rays + i * ray_counts[0], ray_counts[0],
			get_line_angle(i, ray_counts[1]), cylinder);
	}
}
