/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:01:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:35:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
**	Interpolates the uv coordinates for a 2d point based on barycentric
**	coordinates
*/
void			l3d_interpolate_uv(t_triangle *triangle, float *baryc,
									t_vec2 uv)
{
	float	az;
	float	bz;
	float	cz;
	float	inv_denom;

	az = 1.0 / triangle->vtc[0]->pos[2];
	bz = 1.0 / triangle->vtc[1]->pos[2];
	cz = 1.0 / triangle->vtc[2]->pos[2];
	inv_denom = 1.0 / (baryc[0] * az + baryc[1] * bz + baryc[2] * cz);
	uv[0] = ((baryc[0] * triangle->uvs[0][0]) * az +
			(baryc[1] * triangle->uvs[1][0]) * bz +
			(baryc[2] * triangle->uvs[2][0]) * cz) * inv_denom;
	uv[1] = 1 - ((baryc[0] * triangle->uvs[0][1]) * az +
			(baryc[1] * triangle->uvs[1][1]) * bz +
			(baryc[2] * triangle->uvs[2][1]) * cz) * inv_denom;
}

/*
** Loop uvs so that they are always between 0 and 1. If they go above 1
** they continue from 0 and vice versa.
*/
void			l3d_loop_uv(t_vec2 uv)
{
	float	uv_abs[2];

	if (uv[0] > 1.0)
		uv[0] -= floor(uv[0]);
	else if (uv[0] < 0.0)
	{
		uv_abs[0] = fabs(uv[0]);
		uv[0] = 1.0 - (uv_abs[0] - floor(uv_abs[0]));
	}
	if (uv[1] > 1.0)
		uv[1] -= floor(uv[1]);
	else if (uv[1] < 0.0)
	{
		uv_abs[1] = fabs(uv[1]);
		uv[1] = 1.0 - (uv_abs[1] - floor(uv_abs[1]));
	}
}
