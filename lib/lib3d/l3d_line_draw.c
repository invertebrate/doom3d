/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_line_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:22:57 by ohakola          ###   ########.fr       */
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
	xy[0] = edge[0][0] - 1;
	while (++xy[0] <= edge[1][0])
	{
		l3d_pixel_plot(buffer, dimensions_wh, xy, color);
		if (dyi[0] > 0)
		{
			xy[1] += dyi[1];
			dyi[0] -= 2 * dxy[0];
		}
		dyi[0] += 2 * dxy[1];
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
	xy[1] = edge[0][1] - 1;
	while (++xy[1] <= edge[1][1])
	{
		l3d_pixel_plot(buffer, dimensions_wh, xy, color);
		if (dxi[0] > 0)
		{
			xy[0] += dxi[1];
			dxi[0] -= 2 * dxy[1];
		}
		dxi[0] += 2 * dxy[0];
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
*/

void			l3d_line_draw(uint32_t *buffer, uint32_t dimensions_wh[2],
				int32_t edge[2][2], uint32_t color)
{
	int			x1;
	int			x2;
	int			y1;
	int			y2;

	x1 = edge[0][0];
	x2 = edge[1][0];
	y1 = edge[0][1];
	y2 = edge[1][1];
	if (ft_abs(y2 - y1) < ft_abs(x2 - x1))
	{
		if (x1 > x2)
			l3d_line_edge_end_swap(edge);
		l3d_line_plot_low(buffer, dimensions_wh, edge, color);
	}
	else
	{
		if (y1 > y2)
			l3d_line_edge_end_swap(edge);
		l3d_line_plot_high(buffer, dimensions_wh, edge, color);
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
