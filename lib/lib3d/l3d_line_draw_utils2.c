/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_line_draw_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:08:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:42:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static t_bool	same_signs(float a, float b)
{
	return (a != 0 && b != 0 && a * b >= 0);
}

static void		set_intesection(float coefs[6], float denom, t_vec2 intersect)
{
	float	offset;
	float	num;

	offset = denom < 0 ? -denom / 2 : denom / 2;
	num = coefs[2] * coefs[5] - coefs[3] * coefs[4];
	intersect[0] = (num < 0 ? num - offset : num + offset) / denom;
	num = coefs[1] * coefs[4] - coefs[0] * coefs[5];
	intersect[1] = (num < 0 ? num - offset : num + offset) / denom;
}

/*
** Calculate if 2d lines intersect
*/

int32_t			l3d_2d_lines_intersect(t_vec2 edge1[2], t_vec2 edge2[2],
					t_vec2 intersect)
{
	float	coefs[6];
	float	signs[4];
	float	denom;

	coefs[0] = edge1[1][1] - edge1[0][1];
	coefs[2] = edge1[0][0] - edge1[1][0];
	coefs[4] = edge1[1][0] * edge1[0][1] - edge1[0][0] * edge1[1][1];
	signs[2] = coefs[0] * edge2[0][0] + coefs[2] * edge2[0][1] + coefs[4];
	signs[3] = coefs[0] * edge2[1][0] + coefs[2] * edge2[1][1] + coefs[4];
	if (same_signs(signs[2], signs[3]))
		return (0);
	coefs[1] = edge2[1][1] - edge2[0][1];
	coefs[3] = edge2[0][0] - edge2[1][0];
	coefs[5] = edge2[1][0] * edge2[0][1] - edge2[0][0] * edge2[1][1];
	signs[0] = coefs[1] * edge1[0][0] + coefs[3] * edge1[0][1] + coefs[5];
	signs[1] = coefs[1] * edge1[1][0] + coefs[3] * edge1[1][1] + coefs[5];
	if (same_signs(signs[0], signs[1]))
		return (0);
	denom = coefs[0] * coefs[3] - coefs[1] * coefs[2];
	if (denom == 0)
		return (2);
	set_intesection(coefs, denom, intersect);
	return (1);
}

/*
** Draws a triangle wireframe using Bresenham's line drawing algorithm.
** Draw order AB, BC, CA
*/

void			l3d_triangle_2d_draw(uint32_t *buffer,
				uint32_t dimensions_wh[2],
				t_vec2 corners[3], uint32_t color)
{
	l3d_line_draw(buffer, dimensions_wh,
		(int32_t[2][2]){{corners[0][0], corners[0][1]},
			{corners[1][0], corners[1][1]}}, color);
	l3d_line_draw(buffer, dimensions_wh,
		(int32_t[2][2]){{corners[1][0], corners[1][1]},
			{corners[2][0], corners[2][1]}}, color / 2);
	l3d_line_draw(buffer, dimensions_wh,
		(int32_t[2][2]){{corners[2][0], corners[2][1]},
			{corners[0][0], corners[0][1]}}, color / 3);
}

/*
** Swap ends of an edge
*/

void			l3d_line_edge_end_swap(int32_t edge[2][2])
{
	int32_t	tmp[2];

	tmp[0] = edge[0][0];
	tmp[1] = edge[0][1];
	edge[0][0] = edge[1][0];
	edge[0][1] = edge[1][1];
	edge[1][0] = tmp[0];
	edge[1][1] = tmp[1];
}
