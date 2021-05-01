/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_raster.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/01 22:55:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

static void	scan_line(t_sub_framebuffer *buffers,
				float *limits, t_triangle *triangle)
{
	int32_t			x;
	int32_t			y;
	int32_t			end_x;

	y = floor(limits[2]);
	x = fmax(floor(limits[0]), -buffers->x_offset);
	end_x = fmin(floor(limits[1]), buffers->width - buffers->x_offset);
	while (x < end_x)
		l3d_raster_draw_pixel(buffers, (int32_t[2]){x++, y}, triangle);
}

static void	raster_upper(t_sub_framebuffer *bufs,
				t_triangle *tri, t_raster_data *data)
{
	float		x;
	float		y;
	float		end_x;
	float		end_y;
	float		limits[3];

	y = fmax(data->y1, -bufs->y_offset);
	end_y = fmin(data->y2, bufs->height - bufs->y_offset);
	while (y < end_y)
	{
		x = data->x2 + data->slope_ab * (y - data->y2);
		end_x = data->x1 + data->slope_ac * (y - data->y1);
		limits[0] = fmin(x, end_x);
		limits[1] = fmax(x, end_x);
		limits[2] = y;
		scan_line(bufs, limits, tri);
		y++;
	}
}

static void	raster_lower(t_sub_framebuffer *bufs,
				t_triangle *tri, t_raster_data *data)
{
	float		x;
	float		y;
	float		end_x;
	float		end_y;
	float		limits[3];

	y = fmax(data->y2, -bufs->y_offset);
	end_y = fmin(data->y3, bufs->height - bufs->y_offset);
	while (y < end_y)
	{
		x = data->x2 + data->slope_bc * (y - data->y2);
		end_x = data->x1 + data->slope_ac * (y - data->y1);
		limits[0] = fmin(x, end_x);
		limits[1] = fmax(x, end_x);
		limits[2] = y;
		scan_line(bufs, limits, tri);
		y++;
	}
}

/*
** Rasterize triangle
*/

void	l3d_triangle_raster(t_sub_framebuffer *buffers,
			t_triangle *triangle)
{
	t_raster_data	data;
	t_vec2			ordered_points_2d[3];

	if (triangle->material->shading_opts & e_shading_invisible
		|| triangle->material->shading_opts & e_shading_temp_invisible)
		return ;
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
