/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_raster_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:07:32 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 18:08:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void			l3d_order_corners_y(t_vec2 *ordered_corners, t_vec2 *points_2d)
{
	size_t	indices[3];

	ft_min_double_idx((double[3]){points_2d[0][1], points_2d[1][1],
		points_2d[2][1]}, 3, &(indices[0]));
	ml_vector2_copy(points_2d[indices[0]], ordered_corners[0]);
	ft_max_double_idx((double[3]){points_2d[0][1],
		points_2d[1][1], points_2d[2][1]}, 3, &(indices[2]));
	ml_vector2_copy(points_2d[indices[2]], ordered_corners[2]);
	indices[1] = 3 - (indices[0] + indices[2]);
	ml_vector2_copy(points_2d[indices[1]], ordered_corners[1]);
}

float			l3d_z_val(float baryc[3], t_triangle *triangle)
{
	return (((baryc[0] * triangle->vtc_zvalue[0] +
			baryc[1] * triangle->vtc_zvalue[1] +
			baryc[2] * triangle->vtc_zvalue[2])));
}
