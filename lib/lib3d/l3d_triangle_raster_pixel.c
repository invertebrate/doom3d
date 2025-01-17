/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_raster_pixel.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:15:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/30 15:49:58 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

static void	shade_special(t_triangle *triangle, t_vec2 uv, uint32_t *pixel,
	t_vec3 baryc)
{
	if ((triangle->material->shading_opts & e_shading_normal_map)
		&& triangle->material->normal_map)
		*pixel = l3d_pixel_normal_shaded(*pixel, triangle, uv, baryc);
	if (triangle->material->shading_opts & e_shading_select)
		*pixel = l3d_pixel_selection_shaded(*pixel);
}

static uint32_t	pixel_trans(t_triangle *triangle, t_vec2 uv,
					t_vec3 baryc)
{
	uint32_t		pixel;
	t_shading_opts	shading;

	shading = triangle->material->shading_opts;
	if (triangle->material->texture)
	{
		pixel = l3d_sample_texture(triangle->material->texture, uv);
		if ((shading & e_shading_blue_highlight))
			pixel = l3d_color_blend_u32(get_pixel_initial_color_trans(triangle),
					pixel, 0.5);
		if ((shading & e_shading_zero_alpha) && (pixel & 255) == 0)
			return (UINT32_MAX);
	}
	else
		pixel = get_pixel_initial_color_trans(triangle);
	shade_special(triangle, uv, &pixel, baryc);
	if ((shading & e_shading_luminous) || (shading & e_shading_lit))
		return (pixel);
	return (l3d_pixel_light_shaded(triangle, baryc, pixel));
}

static uint32_t	pixel_color(t_triangle *triangle, t_vec2 uv,
					t_vec3 baryc)
{
	uint32_t		pixel;
	t_shading_opts	shading;

	shading = triangle->material->shading_opts;
	if (triangle->material->texture)
	{
		pixel = l3d_sample_texture(triangle->material->texture, uv);
		if ((shading & e_shading_blue_highlight))
		{
			pixel = l3d_color_blend_u32(get_pixel_initial_color(triangle),
					pixel, 0.5);
		}
		if ((shading & e_shading_zero_alpha) && (pixel & 255) == 0)
			return (UINT32_MAX);
	}
	else
		pixel = get_pixel_initial_color(triangle);
	shade_special(triangle, uv, &pixel, baryc);
	if ((shading & e_shading_luminous) || (shading & e_shading_lit))
		return (pixel);
	return (l3d_pixel_light_shaded(triangle, baryc, pixel));
}

/*
** Draw the actual pixel color at the final stage of rasterization
** Shade the pixel according to shading information
*/

void	l3d_raster_draw_pixel(t_sub_framebuffer *buffers, int32_t xy[2],
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
		l3d_clamp_or_repeat_uv(triangle, uv);
		pixel = pixel_color(triangle, uv, baryc);
		if (pixel == UINT32_MAX
			&& triangle->material->shading_opts & e_shading_zero_alpha)
			return ;
		l3d_pixel_plot(buffers->buffer, (uint32_t[2]){buffers->width,
			buffers->height}, offset_xy, pixel);
		l3d_write_z_val(buffers, triangle, offset_xy, z_val);
	}
}

/*
** Draw pixel at the final stage of rasterization for transparent objects
*/

void	l3d_raster_draw_pixel_transparent(t_sub_framebuffer *buffers,
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
		l3d_clamp_or_repeat_uv(triangle, brc_uv[1]);
		pixel = pixel_trans(triangle, brc_uv[1], brc_uv[0]);
		if (pixel == UINT32_MAX
			&& triangle->material->shading_opts & e_shading_zero_alpha)
			return ;
		pixel = l3d_blend_pixel(buffers, offset_xy, pixel);
		l3d_pixel_plot(buffers->buffer, (uint32_t[2]){buffers->width,
			buffers->height}, offset_xy, pixel);
		if ((pixel & 255) == 255)
			l3d_write_z_val(buffers, triangle, offset_xy, z_val);
	}
}
