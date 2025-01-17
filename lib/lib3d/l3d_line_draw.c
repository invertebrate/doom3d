/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_line_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/01 22:23:29 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

static void	init_line_draw_params(int dxy[2], int dx_or_y_i[2],
					int32_t edge[2][2])
{
	dxy[0] = edge[1][0] - edge[0][0];
	dxy[1] = edge[1][1] - edge[0][1];
	dx_or_y_i[1] = 1;
}

static void	l3d_line_plot_low(uint32_t *buffer, uint32_t dims_wh[2],
				int32_t edge[2][2], uint32_t color)
{
	int32_t		dxy[2];
	int32_t		dyi[2];
	int32_t		xy[2];

	init_line_draw_params(dxy, dyi, edge);
	if (dxy[1] < 0)
	{
		dyi[1] = -1;
		dxy[1] = -dxy[1];
	}
	dyi[0] = 2 * dxy[1] - dxy[0];
	xy[1] = edge[0][1];
	xy[0] = edge[0][0];
	while (xy[0] < edge[1][0] && xy[0] < (int32_t)dims_wh[0] && xy[0] >= 0)
	{
		if (xy[1] >= 0 && xy[1] < (int32_t)dims_wh[1])
			l3d_pixel_plot(buffer, dims_wh, xy, color);
		if (dyi[0] > 0)
		{
			xy[1] += dyi[1];
			dyi[0] -= 2 * dxy[0];
		}
		dyi[0] += 2 * dxy[1];
		xy[0]++;
	}
}

static void	l3d_line_plot_high(uint32_t *buffer, uint32_t dims_wh[2],
				int32_t edge[2][2], uint32_t color)
{
	int32_t	dxy[2];
	int32_t	dxi[2];
	int32_t	xy[2];

	init_line_draw_params(dxy, dxi, edge);
	if (dxy[0] < 0)
	{
		dxi[1] = -1;
		dxy[0] = -dxy[0];
	}
	dxi[0] = 2 * dxy[0] - dxy[1];
	xy[0] = edge[0][0];
	xy[1] = edge[0][1];
	while (xy[1] < edge[1][1] && xy[1] < (int32_t)dims_wh[1] && xy[1] >= 0)
	{
		if (xy[0] >= 0 && xy[0] < (int32_t)dims_wh[0])
			l3d_pixel_plot(buffer, dims_wh, xy, color);
		if (dxi[0] > 0)
		{
			xy[0] += dxi[1];
			dxi[0] -= 2 * dxy[1];
		}
		dxi[0] += 2 * dxy[0];
		xy[1]++;
	}
}

static void	line_draw_clamped_edge(uint32_t *buffer,
				uint32_t dimensions_wh[2],
				int32_t clamped[2][2], uint32_t color)
{
	if (ft_abs(clamped[1][1] - clamped[0][1])
		< ft_abs(clamped[1][0] - clamped[0][0]))
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
** Bresenham's line drawing algorithm on given buffer and dimensions
** https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Optimization
** But limited between buffer dimensions to save calculations
*/

void	l3d_line_draw(uint32_t *buffer, uint32_t dimensions_wh[2],
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
			{dimensions_wh[0], dimensions_wh[1]}},
		edgef, is_intersect, intersects))
		return ;
	clamped[0][0] = (int32_t)edgef[0][0];
	clamped[0][1] = (int32_t)edgef[0][1];
	clamped[1][0] = (int32_t)edgef[1][0];
	clamped[1][1] = (int32_t)edgef[1][1];
	line_draw_clamped_edge(buffer, dimensions_wh, clamped, color);
}
