/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:27:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 15:46:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Shade pixel so that further ones in 3d space are darker
*/

uint32_t		l3d_pixel_depth_shaded(uint32_t pixel, float z_val)
{
	float	intensity;

	intensity = 10.0;
	return (l3d_color_blend_u32(pixel, 0x000000ff,
		1.0 - (ft_abs(z_val) * intensity)));
}

/*
** Shade selected object with `e_shading_selected`
*/

uint32_t		l3d_pixel_selection_shaded(uint32_t pixel)
{
	return (l3d_color_blend_u32(pixel, 0x00ff00ff, 0.2));
}

static void		get_world_pos_persp_corr(t_triangle *triangle, t_vec3 baryc,
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
		world_pos[i] = ((baryc[0] * triangle->vtc[0]->pos[i]) * az +
						(baryc[1] * triangle->vtc[1]->pos[i]) * bz +
						(baryc[2] * triangle->vtc[2]->pos[i]) * cz) * inv_denom;
}

static void		flashlight_light_calculation(t_triangle *triangle,
											t_vec3 world_pos,
											uint32_t light[4])
{
	uint32_t		light_add[4];
	float			vars[3];
	float			intensity;
	float			distance;
	float			orth_distance;
	float			radius_at_point;
	void			*test;
static int c = 0;
c++;
	l3d_u32_to_rgba(0xffffffff, light_add);
	light_add[3] = 255;
	ml_vector3_set_all(vars, 0.0);
	test = point_inside_cone(&(triangle->material->flashlight->cone), world_pos, vars);
	if (vars[0] <= triangle->material->flashlight->cone.height && test != NULL)
	{
		distance = vars[0];
		orth_distance = vars[2];
		radius_at_point = vars[1];

		intensity = triangle->material->flashlight->intensity * (1 - (distance /
						triangle->material->flashlight->cone.height));
		intensity *=	(1 - (orth_distance / radius_at_point));
		light[0] += intensity * light_add[0];
		light[1] += intensity * light_add[1];
		light[2] += intensity * light_add[2];
	}
}

void			point_light_calculation(t_triangle *triangle, t_vec3 world_pos,
					uint32_t light[4])
{
	t_vec3		light_dir;
	int32_t		i;
	float		distance;
	float		intensity;
	uint32_t	light_add[4];

	i = -1;
	while (++i < (int32_t)triangle->material->num_lights)
	{
		l3d_u32_to_rgba(triangle->material->light_sources[i].color, light_add);
		ml_vector3_sub(world_pos,
			triangle->material->light_sources[i].pos, light_dir);
		distance = ml_vector3_mag(light_dir);
		if (distance < triangle->material->light_sources[i].radius)
		{
			intensity =
				(1.0 - distance / triangle->material->light_sources[i].radius) *
				triangle->material->light_sources[i].intensity;
			light[0] += intensity * light_add[0];
			light[1] += intensity * light_add[1];
			light[2] += intensity * light_add[2];
		}
	}
	flashlight_light_calculation(triangle, world_pos, light);
	light[3] = 255;
}

/*
** Shade pixel with lights included
*/

uint32_t		l3d_pixel_light_shaded(t_triangle *triangle,
					t_vec3 baryc, uint32_t pixel)
{
	uint32_t	rgba[4];
	uint32_t	light[4];
	uint32_t	result[4];
	t_vec3		world_pos;
	uint32_t	darkness;

	darkness = 250;
	ft_memset(result, 0, sizeof(result));
	if (triangle->material->num_lights > 0)
	{
		get_world_pos_persp_corr(triangle, baryc, world_pos);
		l3d_u32_to_rgba(pixel, rgba);
		ft_memset(light, 0, sizeof(light));
		point_light_calculation(triangle, world_pos, light);
		calculate_luminosity(rgba, light, darkness);
		return (l3d_rgba_to_u32(rgba));
	}
	return (pixel);
}
