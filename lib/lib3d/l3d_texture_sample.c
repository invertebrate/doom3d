/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_texture_sample.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:00:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 18:01:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
**	Samples the texture with given uv_coordinates
**	x = (floor(U * (width)));
**	y = (floor(V * (height)));
**	index = x + width * y;
*/

uint32_t		l3d_sample_texture(t_surface *texture, t_vec2 uv_point)
{
	int			index;
	float		x;
	float		y;
	uint32_t	default_color;

	default_color = L3D_DEFAULT_COLOR;
	if (!texture->pixels)
		return (default_color);
	x = floor(uv_point[0] * texture->w);
	y = floor(uv_point[1] * texture->h);
	if (x >= (int32_t)texture->w)
		x = (float)(texture->w - 1);
	if (y >= (int32_t)texture->h)
		y = (float)(texture->h - 1);
	index = (int)floor(x) + (int)(floor(y * texture->w));
	if (index >= (int32_t)texture->w * (int32_t)texture->h)
		index = texture->w * texture->h - 1;
	else if (index < 0)
		index = 0;
	return (texture->pixels[index]);
}
