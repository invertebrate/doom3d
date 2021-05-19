/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:29:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 15:14:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static uint32_t	read_main_font(t_doom3d *app,
					t_file_contents *file, int32_t offset)
{
	uint32_t	size;
	void		*rwops;

	ft_memcpy(&size, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	error_check(!(rwops = ft_calloc(size)), "Failed to alloc rwops");
	ft_memcpy(rwops, file->buf + offset, sizeof(size));
	offset += size;
	app->assets.main_font = SDL_RWFromConstMem(rwops, size);
	if (app->is_debug)
		LOG_DEBUG("Add main font of size %d, sdl size: %d", size,
			app->assets.main_font->size(app->assets.main_font));
	return (offset);
}

static uint32_t	read_sdl_fonts(t_doom3d *app,
					t_file_contents *file, int32_t offset)
{
	uint32_t	size;
	void		*rwops;

	offset = read_main_font(app, file, offset);
	ft_memcpy(&size, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	error_check(!(rwops = ft_calloc(size)), "Failed to alloc rwops");
	ft_memcpy(rwops, file->buf + offset, sizeof(size));
	offset += size;
	app->assets.title_font = SDL_RWFromConstMem(rwops, size);
	if (app->is_debug)
		LOG_DEBUG("Add title font of size %d", size);
	ft_memcpy(&size, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	error_check(!(rwops = ft_calloc(size)), "Failed to alloc rwops");
	ft_memcpy(rwops, file->buf + offset, sizeof(size));
	offset += size;
	app->assets.small_font = SDL_RWFromConstMem(rwops, size);
	if (app->is_debug)
		LOG_DEBUG("Add small font of size %d", size);
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
	i = -1;
	while (++i < (int32_t)num_written_tracks)
	{
		ft_memcpy(&size, file->buf + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		if (i < SOUNDS_NUM_TRACKS)
		{
			error_check(!(rwops = ft_calloc(size)), "Failed to alloc rwops");
			ft_memcpy(rwops, file->buf + offset, sizeof(size));
			app->assets.sounds[i] = SDL_RWFromConstMem(rwops, size);
			if (app->is_debug)
				LOG_DEBUG("Add sound of size %d", size);
		}
		offset += size;
	}
	return (read_sdl_fonts(app, file, offset));
}
