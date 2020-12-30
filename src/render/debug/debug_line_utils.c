/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:39:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/30 22:41:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	same_signs(float a, float b)
{
	return (a != 0 && b != 0 && a * b >= 0);
}

int32_t			l3d_2d_lines_intersect(t_vec2 edge1[2], t_vec2 edge2[2],
					t_vec2 intersect)
{
	float	coefs[6];
	float	signs[4];
	float	denom;
	float	offset;
	float	num;

	coefs[0] = edge1[1][1] - edge1[0][1];
	coefs[2] = edge1[0][0] - edge1[1][0];
	coefs[4] = edge1[1][0] * edge1[0][1] - edge1[0][0] * edge1[1][1];
	signs[2] = coefs[0] * edge2[0][0] + coefs[2] * edge2[0][1] + coefs[4];
	signs[3] = coefs[0] * edge2[1][0] + coefs[2] * edge2[1][1] + coefs[4];
	if (same_signs( signs[2], signs[3] ))
		return (0);
	coefs[1] = edge2[1][1] - edge2[0][1];
	coefs[3] = edge2[0][0] - edge2[1][0];
	coefs[5] = edge2[1][0] * edge2[0][1] - edge2[0][0] * edge2[1][1];
	signs[0] = coefs[1] * edge1[0][0] + coefs[3] * edge1[0][1] + coefs[5];
	signs[1] = coefs[1] * edge1[1][0] + coefs[3] * edge1[1][1] + coefs[5];
	if (same_signs( signs[0], signs[1] ))
		return (0);
	denom = coefs[0] * coefs[3] - coefs[1] * coefs[2];
	if (denom == 0)
		return (2);
	offset = denom < 0 ? - denom / 2 : denom / 2;
	num = coefs[2] * coefs[5] - coefs[3] * coefs[4];
	intersect[0] = ( num < 0 ? num - offset : num + offset ) / denom;
	num = coefs[1] * coefs[4] - coefs[0] * coefs[5];
	intersect[1] = ( num < 0 ? num - offset : num + offset ) / denom;
	return (1);
}

t_bool			l3d_point2d_inside_aabb(t_vec2 point,
					t_vec2 aabb[2])
{
	return (point[0] >= aabb[0][0] && point[0] < aabb[1][0] &&
		point[1] >= aabb[0][1] && point[1] < aabb[1][1]);
}
