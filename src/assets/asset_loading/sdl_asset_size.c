/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_asset_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:36:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 17:42:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Size for writing thus one byte for len + actual size
*/

uint32_t	get_sdl_asset_write_size(t_sized_file *file)
{
	return (sizeof(uint32_t) + file->size);
}
