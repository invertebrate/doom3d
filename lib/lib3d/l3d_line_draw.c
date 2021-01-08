/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_line_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/08 23:15:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static void		l3d_line_plot_low(uint32_t *buffer, uint32_t dimensions_wh[2],
				int32_t edge[2][2], uint32_t color)
{
	int		dxy[2];
	int		dyi[2];
	int		xy[2];

	dxy[0] = edge[1][0] - edge[0][0];
	dxy[1] = edge[1][1] - edge[0][1];
	dyi[1] = 1;
	if (dxy[1] < 0)
	{
		dyi[1] = -1;
		dxy[1] = -dxy[1];
	}
	dyi[0] = 2 * dxy[1] - dxy[0];
	xy[1] = edge[0][1];
	xy[0] = edge[0][0];
	while (xy[0] < edge[1][0] && xy[0] < (int32_t)dimensions_wh[0] && xy[0] >= 0)
	{
		if (xy[1] >= 0 && xy[1] < (int32_t)dimensions_wh[1])
			l3d_pixel_plot(buffer, dimensions_wh, xy, color);
		if (dyi[0] > 0)
		{
			xy[1] += dyi[1];
			dyi[0] -= 2 * dxy[0];
		}
		dyi[0] += 2 * dxy[1];
		xy[0]++;
	}
}

static void		l3d_line_plot_high(uint32_t *buffer, uint32_t dimensions_wh[2],
				int32_t edge[2][2], uint32_t color)
{
	int dxy[2];
	int dxi[2];
	int xy[2];

	dxy[0] = edge[1][0] - edge[0][0];
	dxy[1] = edge[1][1] - edge[0][1];
	dxi[1] = 1;
	if (dxy[0] < 0)
	{
		dxi[1] = -1;
		dxy[0] = -dxy[0];
	}
	dxi[0] = 2 * dxy[0] - dxy[1];
	xy[0] = edge[0][0];
	xy[1] = edge[0][1];
	while (xy[1] < edge[1][1] && xy[1] < (int32_t)dimensions_wh[1] && xy[1] >= 0)
	{
		if (xy[0] >= 0 && xy[0] < (int32_t)dimensions_wh[0])
			l3d_pixel_plot(buffer, dimensions_wh, xy, color);
		if (dxi[0] > 0)
		{
			xy[0] += dxi[1];
			dxi[0] -= 2 * dxy[1];
		}
		dxi[0] += 2 * dxy[0];
		xy[1]++;
	}
}

static void		l3d_line_edge_end_swap(int32_t edge[2][2])
{
	int32_t	tmp[2];

	tmp[0] = edge[0][0];
	tmp[1] = edge[0][1];
	edge[0][0] = edge[1][0];
	edge[0][1] = edge[1][1];
	edge[1][0] = tmp[0];
	edge[1][1] = tmp[1];
}

/*
** Bresenham's line drawing algorithm on given buffer and dimensions
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Optimization
** But limited between buffer dimensions to save calculations
*/

void			l3d_line_draw(uint32_t *buffer, uint32_t dimensions_wh[2],
					int32_t edge[2][2], uint32_t color)
{
	t_vec2			edgef[2];
	int32_t			clamped[2][2];
	t_vec2			intersects[4];
	int32_t			is_intersect[4];

	ml_vector2_copy((t_vec2){edge[0][0], edge[0][1]}, edgef[0]);
	ml_vector2_copy((t_vec2){edge[1][0], edge[1][1]}, edgef[1]);
	l3d_edge_aabb_intersections((t_vec2[2]){{0, 0},
		{dimensions_wh[0], dimensions_wh[1]}}, edgef, is_intersect, intersects);
	if (!l3d_clamp_edge_within_aabb((t_vec2[2]){{0, 0},
		{dimensions_wh[0], dimensions_wh[1]}}, edgef, is_intersect, intersects))
		return ;
	clamped[0][0] = (int32_t)edgef[0][0];
	clamped[0][1] = (int32_t)edgef[0][1];
	clamped[1][0] = (int32_t)edgef[1][0];
	clamped[1][1] = (int32_t)edgef[1][1];
	if (ft_abs(clamped[1][1] - clamped[0][1]) <
		ft_abs(clamped[1][0] - clamped[0][0]))
	{
		if (clamped[0][0] > clamped[1][0])
			l3d_line_edge_end_swap(clamped);
		l3d_line_plot_low(buffer, dimensions_wh, clamped, color);
	}
	else
	{
		if (clamped[0][1] > clamped[1][1])
			l3d_line_edge_end_swap(clamped);
		l3d_line_plot_high(buffer, dimensions_wh, clamped, color);
	}
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
