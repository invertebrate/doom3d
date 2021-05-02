/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_ray_collider.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 17:53:57 by veilo             #+#    #+#             */
/*   Updated: 2021/05/02 21:14:57 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static void		rotate_vector(t_vec3 vec, t_vec3 pivot, float angle)
{
	t_mat4	rotation;

	ft_memset(&rotation, 0, sizeof(rotation));
	ml_matrix4_general_rotation(pivot, angle, rotation);
	ml_matrix4_mul_vec3(rotation, vec, vec);
	ml_matrix4_print(rotation);
	ml_vector3_print(vec);
	ft_printf("+============\n");
}

/*
** Returns the angle for the tilt of the semi-circle
*/

static float	get_sphere_angle(int step, int total_steps)
{
	float	result;
	(void)step;
	(void)total_steps;
	result = 0.0;
	return (result);
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
	(void)angle;
	float mul = 0.999;

	i = 0;
	angle_step = M_PI / (float)ray_count;
	ml_vector3_copy(sphere->forward, ray_dir);
	while (++i < ray_count - 1)
	{
		mul *= mul;
		ml_vector3_copy(sphere->forward, ray_dir);
		ft_printf("raycount %d\n", ray_count);
		ft_printf("angle step %f , %f\n", angle_step, angle_step * (180 / M_PI) );
		rotate_vector(ray_dir, sphere->up, (int)i * angle_step);
		ml_vector3_print(ray_dir);
		l3d_ray_set(ray_dir, sphere->pos, &(rays[i]));
		ml_vector3_print(rays[i].dir);
		ml_vector3_mul(rays[i].dir, mul, rays[i].dir);
	}
}

/*
** Creates rays evenly distributed in a spherical manner. ray_counts[0] is the
** amount of rays in the semi-circle and ray_counts[1] is the number of steps when
** rotating the semi-circle around.
*/

void		cast_rays_sphere(t_ray *rays, uint32_t *ray_counts, t_sphere *sphere)
{
	int		i;
	t_vec3	backwards;

	i = 0;
	ml_vector3_copy(sphere->forward, backwards);
	// l3d_ray_set(sphere->forward, sphere->pos, &rays[0]);
	// while (++i < (int)ray_counts[1])
	// {
		cast_rays_semicircle(rays + i, ray_counts[0],
							get_sphere_angle(i, ray_counts[0]), sphere);
	// }
}


