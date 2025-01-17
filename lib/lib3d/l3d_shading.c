/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:27:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/30 22:52:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Shade pixel so that further ones in 3d space are darker
*/

uint32_t	l3d_pixel_depth_shaded(uint32_t pixel, float z_val)
{
	float	intensity;

	intensity = 10.0;
	return (l3d_color_blend_u32(pixel, 0x000000ff,
			1.0 - (ft_abs(z_val) * intensity)));
}

/*
** Shade selected object with `e_shading_selected`
*/

uint32_t	l3d_pixel_selection_shaded(uint32_t pixel)
{
	return (l3d_color_blend_u32(pixel, 0x00ff00ff, 0.2));
}

/*
**	Calculates the light intensity caused by flashlight
**	vars[2]		orthogonal distance from cone axis
**	vars[1]		cone radius at point
**	vars[0]		distance
*/

static void	flashlight_light_calculation(t_triangle *triangle,
											t_vec3 world_pos,
											uint32_t light[4])
{
	uint32_t		light_add[4];
	float			vars[3];
	float			intensity;
	void			*test;

	l3d_u32_to_rgba(0xffffffff, light_add);
	light_add[3] = 255;
	ml_vector3_set_all(vars, 0.0);
	test = point_inside_cone(&(triangle->material->flashlight->cone), world_pos,
			vars);
	if (vars[0] <= triangle->material->flashlight->cone.height && test != NULL)
	{
		intensity = triangle->material->flashlight->intensity * (1 - (vars[0]
					/ triangle->material->flashlight->cone.height));
		intensity *= (1 - (vars[2] / vars[1]));
		light[0] += intensity * light_add[0];
		light[1] += intensity * light_add[1];
		light[2] += intensity * light_add[2];
	}
}

/*
** Shade pixel with lights included
*/

uint32_t	l3d_pixel_light_shaded(t_triangle *triangle,
					t_vec3 baryc, uint32_t pixel)
{
	uint32_t	rgba[4];
	uint32_t	light[4];
	uint32_t	result[4];
	t_vec3		world_pos;
	uint32_t	darkness;

	darkness = 230;
	ft_memset(result, 0, sizeof(result));
	if (triangle->material->num_lights > 0
		|| (triangle->material->flashlight
			&& triangle->material->flashlight->enabled == true))
	{
		get_world_pos_persp_corr(triangle, baryc, world_pos);
		l3d_u32_to_rgba(pixel, rgba);
		ft_memset(light, 0, sizeof(light));
		point_light_calculation(triangle, world_pos, light);
		if (triangle->material->flashlight
			&& triangle->material->flashlight->active
			&& triangle->material->flashlight->enabled == true)
			flashlight_light_calculation(triangle, world_pos, light);
		calculate_luminosity(rgba, light, darkness);
		light[3] = 255;
		return (l3d_rgba_to_u32(rgba));
	}
	return (pixel);
}
