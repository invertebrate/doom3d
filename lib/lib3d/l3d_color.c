/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:22:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

uint32_t		l3d_rgba_to_u32(uint32_t rgba[4])
{
	return (((rgba[0] & 255) << 24) | ((rgba[1] & 255) << 16) |
		((rgba[2] & 255) << 8) | (rgba[3] & 255));
}

void			l3d_u32_to_rgba(uint32_t color, uint32_t rgba[4])
{
	rgba[0] = (color >> 24) & 255;
	rgba[1] = (color >> 16) & 255;
	rgba[2] = (color >> 8) & 255;
	rgba[3] = (color & 255);
}

uint32_t		l3d_color_blend_u32(uint32_t color1, uint32_t color2,
				float ratio)
{
	float		i_ratio;
	float		alpha;
	uint32_t	new_color[4];

	alpha = color2 & 255;
	if (alpha == 0)
		return (color1);
	if (ratio >= 1.f)
	{
		ratio = 1.f;
		return (color2);
	}
	else if (ratio < 0.f)
		ratio = 0.f;
	i_ratio = 1.f - ratio;
	new_color[0] = (int)((((color1 >> 24) & 255) * i_ratio) +
		((color2 >> 24) & 255) * ratio);
	new_color[1] = (int)((((color1 >> 16) & 255) * i_ratio) +
		((color2 >> 16) & 255) * ratio);
	new_color[2] = (int)((((color1 >> 8) & 255) * i_ratio) +
		((color2 >> 8) & 255) * ratio);
	new_color[3] = (int)(((color1 & 255) * i_ratio) +
		alpha * ratio);
	return (l3d_rgba_to_u32(new_color));
}

uint32_t		l3d_triangle_normal_color(t_triangle *triangle)
{
	uint32_t	color;

	color = 0x0;
	color |= (uint32_t)(255 * fabs(triangle->normalized_normal[0])) << 8;
	color |= (uint32_t)(255 * fabs(triangle->normalized_normal[1])) << 16;
	color |= (uint32_t)(255 * fabs(triangle->normalized_normal[2])) << 24;
	return (color);
}
