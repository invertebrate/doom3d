/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:27:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/06 00:26:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

uint32_t		l3d_pixel_depth_shaded(uint32_t pixel, float z_val)
{
	float	intensity;

	intensity = 10.0;
	return (l3d_color_blend_u32(pixel, 0x000000ff,
		1.0 - (ft_abs(z_val) * intensity)));
}

uint32_t		l3d_pixel_selection_shaded(uint32_t pixel)
{
	return (l3d_color_blend_u32(pixel, 0x00ff00ff, 0.2));
}

static void		get_world_pos(t_triangle *triangle, t_vec3 baryc,
					t_vec3 world_pos)
{
	int32_t	i;

	i = -1;
	while (++i < 3)
		world_pos[i] = triangle->vtc[0]->pos[i] * baryc[0] +
			triangle->vtc[1]->pos[i] * baryc[1] +
			triangle->vtc[2]->pos[i] * baryc[2];
}

void			point_light_calculation(t_triangle *triangle, t_vec3 baryc,
					uint32_t light[4])
{
	t_vec3		light_dir;
	t_vec3		world_pos;
	int32_t		i;
	float		distance;
	float		attenuation;
	float		intensity;
	uint32_t	light_add[4];

	get_world_pos(triangle, baryc, world_pos);
	l3d_u32_to_rgba(0xffff80ff, light_add);
	i = -1;
	while (++i < (int32_t)triangle->material->num_lights)
	{
		ml_vector3_sub(world_pos,
			triangle->material->light_sources[i].pos, light_dir);
		distance = ml_vector3_mag(light_dir);
		ml_vector3_normalize(light_dir, light_dir);
		if (distance < triangle->material->light_sources[i].radius)
		{
			attenuation =
				1.0 - distance / triangle->material->light_sources[i].radius;
			intensity = attenuation *
				triangle->material->light_sources[i].intensity;
			light[0] += intensity * light_add[0];
			light[1] += intensity * light_add[1];
			light[2] += intensity * light_add[2];
		}
	}
	light[3] = 255;
}

uint32_t		l3d_pixel_light_shaded(t_triangle *triangle,
					t_vec3 baryc, uint32_t pixel)
{
	uint32_t	rgba[4];
	uint32_t	light[4];
	uint32_t	result[4];

	if (triangle->material->num_lights > 0)
	{
		l3d_u32_to_rgba(pixel, rgba);
		ft_memset(light, 0, sizeof(light));
		point_light_calculation(triangle, baryc, light);
		result[0] = (uint32_t)fmin(rgba[0] + light[0], 255.0);
		result[1] = (uint32_t)fmin(rgba[1] + light[1], 255.0);
		result[2] = (uint32_t)fmin(rgba[2] + light[2], 255.0);
		result[3] = rgba[3];
		return (l3d_rgba_to_u32(result));
	}
	return (pixel);
}