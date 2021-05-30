/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_shading_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:04:36 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/31 02:02:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static void	normal_from_color(uint32_t color, t_vec3 normal)
{
	uint32_t	rgba[4];
	float		inv_255;

	inv_255 = 0.00392156862745098;
	l3d_u32_to_rgba(color, rgba);
	normal[0] = (float)rgba[0] * inv_255;
	normal[1] = (float)rgba[1] * inv_255;
	normal[2] = (float)rgba[2] * inv_255;
}

static void	calc_bumped_normal(t_triangle *triangle, t_vec2 uv, t_vec3 res)
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

static float	fragment_get_normal_dot(t_vec3 light_vector, t_vec3 frag_normal)
{
	float		dot;

	ml_vector3_normalize(light_vector, light_vector);
	dot = fabs(ml_vector3_dot(light_vector, frag_normal));
	return (dot);
}

/*
** Return pixel with shading for normal mapping. Only considers the first light
** in a scene and ignores rest.
*/

uint32_t	l3d_pixel_normal_shaded(uint32_t pixel, t_triangle *triangle,
				t_vec2 uv, t_vec3 baryc)
{
	t_vec3		frag_normal;
	t_vec3		light_vector;
	t_vec3		world_pos;
	float		lightness;
	uint32_t	rgba[4];

	lightness = 0;
	l3d_u32_to_rgba(pixel, rgba);
	get_world_pos_persp_corr(triangle, baryc, world_pos);
	ml_vector3_sub(world_pos,
		triangle->material->light_sources[0].pos, light_vector);
	ml_vector3_set(frag_normal, 0, 0, 0);
	calc_bumped_normal(triangle, uv, frag_normal);
	lightness = fragment_get_normal_dot(light_vector, frag_normal);
	rgba[0] *= lightness;
	rgba[1] *= lightness;
	rgba[2] *= lightness;
	return (l3d_rgba_to_u32(rgba));
}
