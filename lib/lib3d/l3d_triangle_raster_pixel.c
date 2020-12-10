/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_raster_pixel.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:15:15 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/07 03:04:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static uint32_t	l3d_get_shaded_pixel(t_triangle *triangle, t_vec2 uv,
					float z_val)
{
	uint32_t	pixel;

	pixel = L3D_DEFAULT_COLOR;
	if (triangle->material)
		pixel = l3d_sample_texture(triangle->material->texture, uv);
	if ((triangle->material->shading_opts & e_shading_zero_alpha) &&
		(pixel & 255) == 0)
		return (UINT32_MAX);
	if (triangle->material->shading_opts & e_shading_normal_map)
		pixel = l3d_pixel_normal_shaded(pixel, triangle, uv);
	if (triangle->material->shading_opts & e_shading_depth)
		pixel = l3d_pixel_depth_shaded(pixel, z_val);
	return (pixel);
}

void			l3d_raster_draw_pixel(t_sub_framebuffer *buffers, int32_t xy[2],
							t_triangle *triangle)
{
	t_vec3		baryc;
	t_vec2		uv;
	float		z_val;
	int32_t		offset_xy[2];
	uint32_t	pixel;

	offset_xy[0] = xy[0] + buffers->x_offset;
	offset_xy[1] = xy[1] + buffers->y_offset;
	l3d_calculate_baryc(triangle->points_2d, (t_vec2){xy[0], xy[1]}, baryc);
	z_val = l3d_z_val(baryc, triangle);
	if (z_val < l3d_pixel_get_float(buffers->zbuffer, (uint32_t[2]){
		buffers->width, buffers->height}, offset_xy))
	{
		l3d_interpolate_uv(triangle, baryc, uv);
		l3d_clamp_uv(uv);
		if ((pixel = l3d_get_shaded_pixel(triangle, uv, z_val)) == UINT32_MAX)
			return ;
		l3d_pixel_plot(buffers->buffer, (uint32_t[2]){buffers->width,
				buffers->height}, offset_xy, pixel);
		if (!(triangle->material->shading_opts & e_shading_ignore_zpass))
			l3d_pixel_plot_float(buffers->zbuffer,
				(uint32_t[2]){buffers->width, buffers->height},
				offset_xy, z_val);
	}
}
