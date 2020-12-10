/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_baryc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:03:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 18:27:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
**	Calculates the barycentric coordinates for a 2d point
*/

void			l3d_calculate_baryc(t_vec2 points_2d[3], t_vec2 point,
					t_vec3 baryc)
{
	float denom;
	float inv_denom;

	denom = ((points_2d[1][1] - points_2d[2][1]) *
			(points_2d[0][0] - points_2d[2][0]) +
			(points_2d[2][0] - points_2d[1][0]) *
			(points_2d[0][1] - points_2d[2][1]));
	if (fabs(denom) < L3D_EPSILON)
		denom = denom < 0 ? -1.0 * L3D_EPSILON : L3D_EPSILON;
	inv_denom = 1 / denom;
	baryc[0] = ((points_2d[1][1] - points_2d[2][1]) *
		(point[0] - points_2d[2][0]) +
		(points_2d[2][0] - points_2d[1][0]) *
		(point[1] - points_2d[2][1])) * inv_denom;
	baryc[1] = ((points_2d[2][1] - points_2d[0][1]) *
		(point[0] - points_2d[2][0]) +
		(points_2d[0][0] - points_2d[2][0]) *
		(point[1] - points_2d[2][1])) * inv_denom;
	baryc[2] = 1 - baryc[0] - baryc[1];
}
