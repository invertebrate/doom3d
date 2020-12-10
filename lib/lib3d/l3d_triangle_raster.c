/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_raster.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/07 14:55:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

static void		scan_line(t_sub_framebuffer *buffers,
							float *limits, t_triangle *triangle)
{
	int32_t			x;
	int32_t			y;
	int32_t			end_x;

	y = floor(limits[2]);
	x = floor(limits[0]);
	end_x = floor(limits[1]);
	while (x < end_x && (x + buffers->x_offset < buffers->width))
	{
		if (x + buffers->x_offset < 0)
		{
			x = -buffers->x_offset;
			continue ;
		}
		l3d_raster_draw_pixel(buffers, (int32_t[2]){x, y}, triangle);
		x++;
	}
}

static void		raster_upper(t_sub_framebuffer *bufs,
								t_triangle *tri, t_raster_data *data)
{
	float		x;
	float		y;
	float		end_x;

	y = data->y1;
	while (y < data->y2 && (y + bufs->y_offset < bufs->height))
	{
		if (y + bufs->y_offset < 0)
		{
			y = -bufs->y_offset;
			continue ;
		}
		x = data->x2 + data->slope_ab * (y - data->y2);
		end_x = data->x1 + data->slope_ac * (y - data->y1);
		if (x < end_x)
			scan_line(bufs, (float[3]){x, end_x + 1, y}, tri);
		else if (x > end_x)
			scan_line(bufs, (float[3]){end_x, x + 1, y}, tri);
		y++;
	}
}

static void		raster_lower(t_sub_framebuffer *bufs,
								t_triangle *tri, t_raster_data *data)
{
	float		x;
	float		y;
	float		end_x;

	y = data->y2;
	while (y < data->y3 && (y + bufs->y_offset < bufs->height))
	{
		if (y + bufs->y_offset < 0)
		{
			y = -bufs->y_offset;
			continue ;
		}
		x = data->x2 + data->slope_bc * (y - data->y2);
		end_x = data->x1 + data->slope_ac * (y - data->y1);
		if (x < end_x)
			scan_line(bufs, (float[3]){x, end_x + 1, y}, tri);
		else if (x > end_x)
			scan_line(bufs, (float[3]){end_x, x + 1, y}, tri);
		y++;
	}
}

void			l3d_triangle_raster(t_sub_framebuffer *buffers,
					t_triangle *triangle)
{
	t_raster_data	data;
	t_vec2			ordered_points_2d[3];

	l3d_order_corners_y(ordered_points_2d, triangle->points_2d);
	data.x1 = floor(ordered_points_2d[0][0]);
	data.x2 = floor(ordered_points_2d[1][0]);
	data.x3 = floor(ordered_points_2d[2][0]);
	data.y1 = floor(ordered_points_2d[0][1]);
	data.y2 = floor(ordered_points_2d[1][1]);
	data.y3 = floor(ordered_points_2d[2][1]);
	data.slope_bc = (data.x3 - data.x2) / (data.y3 - data.y2);
	data.slope_ac = (data.x3 - data.x1) / (data.y3 - data.y1);
	data.slope_ab = (data.x2 - data.x1) / (data.y2 - data.y1);
	raster_upper(buffers, triangle, &data);
	raster_lower(buffers, triangle, &data);
}
