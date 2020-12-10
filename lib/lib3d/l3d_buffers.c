/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_buffers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:49:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static t_sub_framebuffer	*l3d_subbuffer_create(t_framebuffer *parent,
														int32_t x, int32_t y)
{
	t_sub_framebuffer	*sub_buffer;

	error_check(!(sub_buffer = malloc(sizeof(t_sub_framebuffer))),
				"Failed to malloc frame sub buffer");
	sub_buffer->height = parent->height / parent->num_y;
	sub_buffer->width = parent->width / parent->num_x;
	sub_buffer->parent_height = parent->height;
	sub_buffer->parent_width = parent->width;
	sub_buffer->x_start = x * sub_buffer->width;
	sub_buffer->y_start = y * sub_buffer->height;
	sub_buffer->x_offset = sub_buffer->parent_width * 0.5 - sub_buffer->x_start;
	sub_buffer->y_offset = sub_buffer->parent_height * 0.5 -
		sub_buffer->y_start;
	error_check(!(
		sub_buffer->buffer = malloc(sizeof(uint32_t) *
			sub_buffer->height * sub_buffer->width)),
			"Failed to malloc frame sub buffer");
	error_check(!(
		sub_buffer->zbuffer = malloc(sizeof(float) *
			sub_buffer->height * sub_buffer->width)),
			"Failed to malloc frame sub buffer");
	return (sub_buffer);
}

static void					l3d_framebuffer_sub_destroy(
								t_sub_framebuffer *sub_buffer)
{
	if (sub_buffer == NULL)
		return ;
	free(sub_buffer->buffer);
	free(sub_buffer->zbuffer);
	free(sub_buffer);
}

t_framebuffer				*l3d_framebuffer_create(int32_t width,
								int32_t height)
{
	t_framebuffer	*fbuffer;
	int32_t			x;
	int32_t			y;
	int32_t			index;

	error_check(!(fbuffer = malloc(sizeof(t_framebuffer))), "!mallocf");
	error_check(!(fbuffer->buffer =
		malloc(sizeof(uint32_t) * width * height)), "Failed to malloc fbuffer");
	fbuffer->num_x = L3D_BUFFER_SPLIT_SIZE_X;
	fbuffer->num_y = L3D_BUFFER_SPLIT_SIZE_Y;
	fbuffer->width = width;
	fbuffer->height = height;
	error_check(!(fbuffer->sub_buffers = malloc(sizeof(t_sub_framebuffer*) *
		fbuffer->num_y * fbuffer->num_x)), "Failed to malloc sbuffer");
	y = -1;
	while (++y < fbuffer->num_y)
	{
		x = -1;
		while (++x < fbuffer->num_x)
		{
			index = y * fbuffer->num_x + x;
			fbuffer->sub_buffers[index] = l3d_subbuffer_create(fbuffer, x, y);
		}
	}
	return (fbuffer);
}

void						l3d_framebuffer_destroy(t_framebuffer *framebuffer)
{
	int32_t		i;

	if (framebuffer != NULL)
	{
		i = -1;
		while (++i < framebuffer->num_x * framebuffer->num_y)
			l3d_framebuffer_sub_destroy(framebuffer->sub_buffers[i]);
		free(framebuffer->sub_buffers);
		free(framebuffer->buffer);
		free(framebuffer);
		framebuffer = NULL;
	}
}

void						l3d_framebuffer_recreate(t_framebuffer **buffer,
												int32_t width, int32_t height)
{
	if (buffer != NULL && *buffer != NULL)
		l3d_framebuffer_destroy(*buffer);
	*buffer = l3d_framebuffer_create(width, height);
}
