/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:27:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 18:11:10 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static void		normal_from_color(uint32_t color, t_vec3 normal)
{
	uint32_t	rgba[4];
	float		inv_255;

	inv_255 = 0.00392156862745098;
	l3d_u32_to_rgba(color, rgba);
	normal[0] = (float)rgba[0] * inv_255;
	normal[1] = (float)rgba[1] * inv_255;
	normal[2] = (float)rgba[2] * inv_255;
}

static void		calc_bumped_normal(t_triangle *triangle, t_vec2 uv, t_vec3 res)
{
	uint32_t	normal_value;
	t_vec3		bumpnormal;
	t_vec3		resultnormal;
	t_mat3		tbn;

	normal_value = l3d_sample_texture(triangle->material->normal_map, uv);
	normal_from_color(normal_value, bumpnormal);
	ml_vector3_mul(bumpnormal, 2, bumpnormal);
	ml_vector3_sub(bumpnormal, (t_vec3){1.0, 1.0, 1.0}, bumpnormal);
	ml_matrix3_column(triangle->tangent, triangle->bitangent,
		triangle->normalized_normal, tbn);
	ml_matrix3_mul_vec3(tbn, bumpnormal, resultnormal);
	ml_vector3_normalize(resultnormal, res);
}

static uint32_t	fragment_shade_normal(t_vec3 light_vector, t_vec3 frag_normal,
									uint32_t frag)
{
	float		dot;
	uint32_t	rgba[4];
	int			i;

	i = -1;
	dot = ml_vector3_dot(light_vector, frag_normal);
	l3d_u32_to_rgba(frag, rgba);
	while (++i < 3)
	{
		rgba[i] *= fabs(dot);
	}
	rgba[3] = 255;
	return (l3d_rgba_to_u32(rgba));
}

uint32_t		l3d_pixel_normal_shaded(uint32_t pixel, t_triangle *triangle,
					t_vec2 uv)
{
	t_vec3 frag_normal;
	t_vec3 light_vector;

	ml_vector3_set(light_vector, 0.0, 0.0, -1.0);
	ml_vector3_set(frag_normal, 0.0, 0.0, -1.0);
	calc_bumped_normal(triangle, uv, frag_normal);
	return (fragment_shade_normal(light_vector, frag_normal, pixel));
}

uint32_t		l3d_pixel_depth_shaded(uint32_t pixel, float z_val)
{
	float	intensity;

	intensity = 5.0;
	return (l3d_color_blend_u32(pixel, 0x000000ff,
		1.0 - (ft_abs(z_val) * intensity)));
}
