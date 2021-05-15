/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_sprites_and_hud.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:42:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 21:04:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	sprites_and_hud_destroy(t_assets *assets)
{
	t_surface	*texture;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)assets->asset_files.num_sprites)
	{
		texture = hash_map_get(assets->sprite_textures,
				(int64_t)assets->asset_files.sprite_files[i]);
		if (texture)
			free(texture->pixels);
	}
	hash_map_destroy_free(assets->sprite_textures);
	i = -1;
	while (++i < (int32_t)assets->asset_files.num_hud_textures)
	{
		texture = hash_map_get(assets->hud_textures,
				(int64_t)assets->asset_files.hud_textures[i]);
		if (texture)
			free(texture->pixels);
	}
	hash_map_destroy_free(assets->hud_textures);
}
