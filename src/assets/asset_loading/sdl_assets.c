/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:49:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 22:55:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Allocates space for an SDL loaded file to be saved into memory.
** These SDL_Rwops must be freed manually using free
*/

SDL_RWops	*sdl_asset_as_memory(const char *filename)
{
	SDL_RWops	*rw_file;
	size_t		size;
	void		*buffer;

	rw_file =  SDL_RWFromFile(filename, "rb");
	size = rw_file->size(rw_file);
	buffer = ft_calloc(size);
	error_check(!buffer, "Failed to malloc font buffer");
	rw_file->read(rw_file, buffer, 1, size);
	rw_file->close(rw_file);
	return (SDL_RWFromConstMem(buffer, size));
}
