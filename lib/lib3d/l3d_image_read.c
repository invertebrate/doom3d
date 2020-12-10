/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_image_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 23:46:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

/*
** Corrects bmp pixel colors to RGBA
*/

static void		l3d_bmp_pixel_correct(t_image_data *image, uint32_t i)
{
	unsigned char			rgb[3];

	rgb[0] = image->pixels[i + 2];
	rgb[1] = image->pixels[i + 1];
	rgb[2] = image->pixels[i + 0];
	image->pixels[i + 0] = rgb[0];
	image->pixels[i + 1] = rgb[1];
	image->pixels[i + 2] = rgb[2];
}

/*
** Flips rows, because bmp pixel data has y inverted. At the end colors are
** transformed to RGBA.
** If height is negative, vertical flip does not happen.
** ToDo if needed: Handle negative width (reverse row pixels)
*/

static void		l3d_handle_bmp_pixels(t_image_data *image,
					t_bmp_file_header *header)
{
	int32_t			i;
	unsigned char	*temp_row;
	uint32_t		width;

	temp_row = malloc(sizeof(char) * image->width * image->bytes_per_pixel);
	if (header->height > 0)
	{
		i = -1;
		width = image->width * image->bytes_per_pixel;
		while (++i < (int32_t)image->height / 2)
		{
			ft_memcpy(temp_row, image->pixels + (i * width), width);
			ft_memcpy(image->pixels + (i * width),
				image->pixels + (image->height - i - 1) * width, width);
			ft_memcpy(image->pixels + (image->height - i - 1) * width,
				temp_row, width);
		}
	}
	free(temp_row);
	i = 0;
	while (i < (int32_t)(header->size - header->data_offset))
	{
		l3d_bmp_pixel_correct(image, i);
		i += image->bytes_per_pixel;
	}
}

/*
** Reads a bmp image into t_image_data *image res result.
** Assumes all bmps are either 24 or 32 bit images (for our purposes)
*/

static void		l3d_read_bmp_image(const char *filename,
					t_image_data *image_res)
{
	t_file_contents			*file;
	t_bmp_file_header		header;
	uint32_t				image_size;
	void					*buf;

	file = read_file(filename);
	buf = file->buf;
	ft_memcpy(&header, buf, sizeof(header));
	error_check(header.file_type != 0x4D42, "Invalid bmp image");
	image_size = header.size - header.data_offset;
	error_check(!(image_res->pixels = malloc(sizeof(char) * image_size)),
		"Failed to malloc image pixels");
	ft_memcpy(image_res->pixels, buf + header.data_offset, image_size);
	image_res->bytes_per_pixel = header.bits_per_pixel / 8;
	error_check(!(image_res->bytes_per_pixel == 3 ||
		image_res->bytes_per_pixel == 4), "Bmp image not 24 nor 32 bit");
	image_res->width = ft_abs(header.width);
	image_res->height = ft_abs(header.height);
	l3d_handle_bmp_pixels(image_res, &header);
	destroy_file_contents(file);
}

/*
** Reads bmp image into uint32_t **pixels_out data. Saves width and height.
** Replaces alpha with 255 if image was only 24 bit.
*/

void			l3d_read_bmp_image_32bit_rgba(const char *filename,
				uint32_t **pixels_out, uint32_t *width, uint32_t *height)
{
	t_image_data		image;
	int32_t				i;
	int32_t				j;
	uint32_t			rgba;

	l3d_read_bmp_image(filename, &image);
	error_check(!(*pixels_out =
		malloc(sizeof(uint32_t) * image.width * image.height)),
		"Failed to malloc 32 bit pixels");
	i = 0;
	j = 0;
	while (i < (int32_t)(image.height * image.width))
	{
		rgba = l3d_rgba_to_u32((uint32_t[4]){image.pixels[j],
			image.pixels[j + 1], image.pixels[j + 2],
			image.bytes_per_pixel == 4 ? image.pixels[j + 3] : 0xFF});
		ft_memcpy(*pixels_out + i, &rgba, sizeof(uint32_t));
		j += image.bytes_per_pixel;
		i++;
	}
	*width = image.width;
	*height = image.height;
	free(image.pixels);
}

t_surface		*l3d_read_bmp_32bit_rgba_surface(const char *filename)
{
	t_surface	*surface;

	surface = malloc(sizeof(t_surface));
	if (!surface)
		return (NULL);
	l3d_read_bmp_image_32bit_rgba(filename, &surface->pixels,
		&surface->w, &surface->h);
	return (surface);
}
