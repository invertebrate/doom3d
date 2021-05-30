/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_shading_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:35:04 by veilo             #+#    #+#             */
/*   Updated: 2021/05/30 22:56:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void	get_world_pos_persp_corr(t_triangle *triangle, t_vec3 baryc,
			t_vec3 world_pos)
{
	int32_t	i;
	float	az;
	float	bz;
	float	cz;
	float	inv_denom;

	az = 1.0 / triangle->vtc[0]->pos[2];
	bz = 1.0 / triangle->vtc[1]->pos[2];
	cz = 1.0 / triangle->vtc[2]->pos[2];
	inv_denom = 1.0 / (baryc[0] * az + baryc[1] * bz + baryc[2] * cz);
	i = -1;
	while (++i < 3)
		world_pos[i] = ((baryc[0] * triangle->vtc[0]->pos[i]) * az
				+ (baryc[1] * triangle->vtc[1]->pos[i]) * bz
				+ (baryc[2] * triangle->vtc[2]->pos[i]) * cz) * inv_denom;
}

static void	normalize_with_mag(float mag, t_vec3 res)
{
	res[0] = res[0] / mag;
	res[1] = res[1] / mag;
	res[2] = res[2] / mag;
}

void	point_light_calculation(t_triangle *triangle, t_vec3 world_pos,
			uint32_t light[4])
{
	t_vec3		light_dir;
	int32_t		i;
	float		dist;
	float		intens;
	uint32_t	light_add[4];

	i = -1;
	while (++i < (int32_t)triangle->material->num_lights)
	{
		l3d_u32_to_rgba(triangle->material->light_sources[i].color, light_add);
		ml_vector3_sub(world_pos,
			triangle->material->light_sources[i].pos, light_dir);
		dist = ml_vector3_mag(light_dir);
		normalize_with_mag(dist, light_dir);
		intens = -ml_vector3_dot(light_dir, triangle->normalized_normal);
		if (dist < triangle->material->light_sources[i].radius && intens >= 0)
		{
			intens *= (1.0 - dist / triangle->material->light_sources[i].radius)
				* triangle->material->light_sources[i].intensity;
			light[0] += intens * light_add[0];
			light[1] += intens * light_add[1];
			light[2] += intens * light_add[2];
		}
	}
}
