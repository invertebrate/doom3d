/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_image_place.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:26:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Usage:
**	l3d_image_place(
**		&(t_surface){
**			.h = app->window->height,
**			.w = app->window->width,
**			.pixels = app->window->buffers->framebuffer->buffer},
**		&(t_surface){
**			.h = height,
**			.w = width,
**			.pixels =texture},
**		(int32_t[2]){50, 50}, 1.0);
*/

void				l3d_image_place(t_surface *frame,
					t_surface *image, int32_t pos_xy[2], float blend_ratio)
{
	uint32_t		frame_pixel;
	uint32_t		layer_pixel;
	int32_t			x;
	int32_t			y;

	y = pos_xy[1] - 1;
	while (++y < pos_xy[1] + (int32_t)image->h)
	{
		x = pos_xy[0] - 1;
		while (++x < pos_xy[0] + (int32_t)image->w)
		{
			layer_pixel = ((uint32_t*)image->pixels)[(y - pos_xy[1]) *
					image->w + (x - pos_xy[0])];
			frame_pixel =
				frame->pixels[y * frame->w + x];
			if (x < (int32_t)frame->w && y < (int32_t)frame->h &&
				x >= 0 && y >= 0)
				frame->pixels[y * (int32_t)frame->w + x] =
					l3d_color_blend_u32(frame_pixel, layer_pixel, blend_ratio);
		}
	}
}

t_surface			*l3d_image_scaled(t_surface *image,
										int32_t dest_x, int32_t dest_y)
{
	float		scales[2];
	int32_t		x;
	int32_t		y;
	t_surface	*image_out;
	int32_t		i;

	error_check(!(image_out = malloc(sizeof(t_surface))), "!Malloc surface");
	error_check(!(image_out->pixels = malloc(sizeof(uint32_t) * dest_x *
		dest_y)), "Failed to malloc pixels");
	image_out->w = dest_x;
	image_out->h = dest_y;
	scales[0] = (float)image->w / (float)dest_x;
	scales[1] = (float)image->h / (float)dest_y;
	y = -1;
	while (++y < (int32_t)image_out->h)
	{
		x = -1;
		while (++x < (int32_t)image_out->w)
		{
			i = (int32_t)((float)y * scales[1]) * image->w +
				(int32_t)((float)x * scales[0]);
			image_out->pixels[y * image_out->w + x] = image->pixels[i];
		}
	}
	return (image_out);
}
