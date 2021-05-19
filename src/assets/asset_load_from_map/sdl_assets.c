/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:29:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 18:20:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static uint32_t	read_font(t_sized_file *font,
					t_file_contents *file, int32_t offset)
{
	ft_memcpy(&font->size, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	error_check(!(font->data = ft_calloc(font->size)), "Failed to alloc rwops");
	ft_memcpy(font->data, file->buf + offset, font->size);
	offset += font->size;
	return (offset);
}

static uint32_t	read_sdl_fonts(t_doom3d *app,
					t_file_contents *file, int32_t offset)
{
	offset = read_font(&app->assets.main_font, file, offset);
	offset = read_font(&app->assets.title_font, file, offset);
	offset = read_font(&app->assets.small_font, file, offset);
	return (offset);
}

uint32_t	read_sdl_assets(t_doom3d *app,
				t_file_contents *file, int32_t offset)
{
	int32_t		i;
	uint32_t	num_written_tracks;

	num_written_tracks = 0;
	ft_memcpy(&num_written_tracks, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	i = -1;
	while (++i < (int32_t)num_written_tracks)
	{
		ft_memcpy(&app->assets.sounds[i].size,
			file->buf + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		error_check(!(app->assets.sounds[i].data
				= ft_calloc(app->assets.sounds[i].size)),
			"Failed to alloc data");
		ft_memcpy(app->assets.sounds[i].data,
			file->buf + offset, sizeof(app->assets.sounds[i].size));
		offset += app->assets.sounds[i].size;
	}
	return (read_sdl_fonts(app, file, offset));
}
