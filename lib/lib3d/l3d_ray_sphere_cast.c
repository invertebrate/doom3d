/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_ray_collider.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:53:57 by veilo             #+#    #+#             */
/*   Updated: 2021/05/03 17:04:08 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"


static void		rotate_vector(t_vec3 vec, t_vec3 pivot, float angle)
{
	t_mat4	rotation;

	ft_memset(&rotation, 0, sizeof(rotation));
	ml_matrix4_general_rotation(pivot, angle, rotation);
	ml_matrix4_mul_vec3(rotation, vec, vec);
}

/*
** Returns the angle for the tilt of the semi-circle
*/

static float	get_sphere_angle(int step, int total_steps)
{
	 return (2 * M_PI * (float)step / (float)total_steps);
}

/*
** Cast ray_count number of rays in a semi-circle. Angle is the amount of tilt
** the semi-circle has around the forward axis. Excludes the ray forward to
** avoid duplication.
*/

static void	cast_rays_semicircle(t_ray *rays, uint32_t ray_count,
								float angle, t_sphere *sphere)
{
	uint32_t	i;
	float		angle_step;
	t_vec3		ray_dir;
	t_vec3		tilted_up;

	i = 0;
	angle_step = M_PI / (float)ray_count;
	ml_vector3_copy(sphere->up, tilted_up);
	ml_vector3_copy(sphere->forward, ray_dir);
	while (++i < ray_count)
	{
		rotate_vector(tilted_up, sphere->forward, angle);
		ml_vector3_copy(sphere->forward, ray_dir);
		rotate_vector(ray_dir, tilted_up, (int)i * angle_step);
		l3d_ray_set(ray_dir, sphere->pos, &(rays[i]));
	}
}

/*
** Creates rays evenly distributed in a spherical manner. ray_counts[0] is the
** amount of rays in the semi-circle and ray_counts[1] is the number of steps when
** rotating the semi-circle around.
*/

void		l3d_cast_rays_sphere(t_ray *rays, uint32_t *ray_counts,
				t_sphere *sphere)
{
	int		i;

	i = 0;
	l3d_ray_set(sphere->forward, sphere->pos, &rays[0]);
	while (++i < (int)ray_counts[1])
	{
		cast_rays_semicircle(rays + i * ray_counts[0], ray_counts[0],
							get_sphere_angle(i, ray_counts[1]), sphere);
	}
}
