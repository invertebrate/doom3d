/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_sprites_and_hud.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:42:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 17:45:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	scene_sprites_and_hud_destroy(t_scene *scene)
{
	t_surface	*texture;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)scene->asset_files.num_sprites)
	{
		texture = hash_map_get(scene->sprite_textures,
				(int64_t)scene->asset_files.sprite_files[i]);
		if (texture)
			free(texture->pixels);
	}
	hash_map_destroy_free(scene->sprite_textures);
	i = -1;
	while (++i < (int32_t)scene->asset_files.num_hud_textures)
	{
		texture = hash_map_get(scene->hud_textures,
				(int64_t)scene->asset_files.hud_textures[i]);
		if (texture)
			free(texture->pixels);
	}
	hash_map_destroy_free(scene->hud_textures);
}
