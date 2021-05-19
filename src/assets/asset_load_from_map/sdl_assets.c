/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:29:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 14:43:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static uint32_t	read_sdl_fonts(t_doom3d *app,
					t_file_contents *file, int32_t offset)
{
	uint32_t	size;
	void		*rwops;

	ft_memcpy(&size, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	error_check(!(rwops = ft_calloc(size)), "Failed to alloc rwops");
	ft_memcpy(rwops, file->buf + offset, sizeof(size));
	offset += size;
	app->assets.main_font = rwops;
	ft_memcpy(&size, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	error_check(!(rwops = ft_calloc(size)), "Failed to alloc rwops");
	ft_memcpy(rwops, file->buf + offset, sizeof(size));
	offset += size;
	app->assets.title_font = rwops;
	ft_memcpy(&size, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	error_check(!(rwops = ft_calloc(size)), "Failed to alloc rwops");
	ft_memcpy(rwops, file->buf + offset, sizeof(size));
	offset += size;
	app->assets.small_font = rwops;
	return (offset);
}

uint32_t	read_sdl_assets(t_doom3d *app,
				t_file_contents *file, int32_t offset)
{
	int32_t		i;
	uint32_t	num_written_tracks;
	uint32_t	size;
	void		*rwops;

	num_written_tracks = 0;
	size = 0;
	ft_memcpy(&num_written_tracks, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	rwops = NULL;
	i = -1;
	while (++i < (int32_t)num_written_tracks)
	{
		ft_memcpy(&size, file->buf + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		if (i < SOUNDS_NUM_TRACKS)
		{
			error_check(!(rwops = ft_calloc(size)), "Failed to alloc rwops");
			ft_memcpy(rwops, file->buf + offset, sizeof(size));
			app->assets.sounds[i] = rwops;
			LOG_WARN("Add sound of size %d", ((SDL_RWops*)rwops)->size(rwops));
		}
		offset += size;
	}
	return (read_sdl_fonts(app, file, offset));
}
