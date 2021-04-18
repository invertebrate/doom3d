/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_raster_pixel.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:15:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 18:35:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static void		shade_pixel(t_triangle *triangle, t_vec2 uv,
					float z_val, uint32_t *pixel)
{
	if ((triangle->material->shading_opts & e_shading_normal_map) &&
		triangle->material->normal_map)
		*pixel = l3d_pixel_normal_shaded(*pixel, triangle, uv);
	if (triangle->material->shading_opts & e_shading_depth)
		*pixel = l3d_pixel_depth_shaded(*pixel, z_val);
	if (triangle->material->shading_opts & e_shading_select)
		*pixel = l3d_pixel_selection_shaded(*pixel);
}

static uint32_t	pixel_trans(t_triangle *triangle, t_vec2 uv,
					t_vec3 baryc, float z_val)
{
	uint32_t	pixel;

	if (triangle->material->shading_opts & e_shading_green)
		pixel = 0x00ff0064;
	else if (triangle->material->shading_opts & e_shading_red)
		pixel = 0xff000064;
	else if (triangle->material->shading_opts & e_shading_yellow)
		pixel = 0xffff0064;
	else if (triangle->material->shading_opts & e_shading_cyan)
		pixel = 0x00ffff64;
	else
		pixel = L3D_DEFAULT_COLOR_TRANSPARENT;
	if (triangle->material->texture)
		pixel = l3d_sample_texture(triangle->material->texture, uv);
	if ((triangle->material->shading_opts & e_shading_zero_alpha) &&
		(pixel & 255) == 0)
		return (UINT32_MAX);
	shade_pixel(triangle, uv, z_val, &pixel);
	pixel = l3d_pixel_light_shaded(triangle, baryc, pixel);
	return (pixel);
}

static uint32_t	pixel_color(t_triangle *triangle, t_vec2 uv,
					t_vec3 baryc, float z_val)
{
	uint32_t	pixel;

	if (triangle->material->shading_opts & e_shading_green)
		pixel = 0x00ff00ff;
	else if (triangle->material->shading_opts & e_shading_red)
		pixel = 0xff0000ff;
	else if (triangle->material->shading_opts & e_shading_yellow)
		pixel = 0xffff00ff;
	else if (triangle->material->shading_opts & e_shading_cyan)
		pixel = 0x00ffffff;
	else
		pixel = L3D_DEFAULT_COLOR;
	if (triangle->material->texture)
		pixel = l3d_sample_texture(triangle->material->texture, uv);
	if ((triangle->material->shading_opts & e_shading_zero_alpha) &&
		(pixel & 255) == 0)
		return (UINT32_MAX);
	shade_pixel(triangle, uv, z_val, &pixel);
	pixel = l3d_pixel_light_shaded(triangle, baryc, pixel);
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
		l3d_loop_uv(uv);
		if ((pixel = pixel_color(triangle, uv, baryc, z_val)) == UINT32_MAX)
			return ;
		l3d_pixel_plot(buffers->buffer, (uint32_t[2]){buffers->width,
				buffers->height}, offset_xy, pixel);
		if (!(triangle->material->shading_opts & e_shading_ignore_zpass))
			l3d_pixel_plot_float(buffers->zbuffer,
				(uint32_t[2]){buffers->width, buffers->height},
				offset_xy, z_val);
	}
}

void			l3d_raster_draw_pixel_transparent(t_sub_framebuffer *buffers,
											int32_t xy[2],
											t_triangle *triangle)
{
	t_vec3		brc_uv[2];
	float		z_val;
	int32_t		offset_xy[2];
	uint32_t	pixel;

	offset_xy[0] = xy[0] + buffers->x_offset;
	offset_xy[1] = xy[1] + buffers->y_offset;
	l3d_calculate_baryc(triangle->points_2d, (t_vec2){xy[0], xy[1]}, brc_uv[0]);
	z_val = l3d_z_val(brc_uv[0], triangle);
	if (z_val < l3d_pixel_get_float(buffers->zbuffer, (uint32_t[2]){
		buffers->width, buffers->height}, offset_xy))
	{
		l3d_interpolate_uv(triangle, brc_uv[0], brc_uv[1]);
		l3d_loop_uv(brc_uv[1]);
		if ((pixel = pixel_trans(triangle,
			brc_uv[1], brc_uv[0], z_val)) == UINT32_MAX)
			return ;
		pixel = l3d_color_alpha_blend_u32(l3d_pixel_get(buffers->buffer,
			(uint32_t[2]){buffers->width, buffers->height}, offset_xy), pixel);
		l3d_pixel_plot(buffers->buffer, (uint32_t[2]){buffers->width,
				buffers->height}, offset_xy, pixel);
	}
}
