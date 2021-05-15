/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:49:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 21:51:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Allocates space for an SDL loaded file to be saved into memory.
** These SDL_Rwops must be freed manually using free
*/

SDL_RWops	*sdl_asset_as_memory(const char *filename)
{
	SDL_RWops	*font_file;
	size_t		size;
	void		*buffer;

	font_file =  SDL_RWFromFile(filename, "rb");
	size = font_file->size(font_file);
	buffer = ft_calloc(size);
	error_check(!buffer, "Failed to malloc font buffer");
	font_file->read(font_file, buffer, 1, size);
	font_file->close(font_file);
	return (buffer);
}
