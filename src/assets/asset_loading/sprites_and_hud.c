/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_and_hud.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:37:19 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 19:30:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	hud_icon_files_set(t_asset_files *data)
{
	data->hud_textures[data->num_hud_textures++]
		= "assets/img/ammo_icon_64.bmp";
	data->hud_textures[data->num_hud_textures++]
		= "assets/img/jetpack_icon_64.bmp";
	data->hud_textures[data->num_hud_textures++]
		= "assets/img/pistol_icon_64.bmp";
	data->hud_textures[data->num_hud_textures++]
		= "assets/img/rpg_icon_64.bmp";
	data->hud_textures[data->num_hud_textures++]
		= "assets/img/health_icon_64.bmp";
	data->hud_textures[data->num_hud_textures++]
		= "assets/img/keycard_icon_64.bmp";
	data->hud_textures[data->num_hud_textures++]
		= "assets/img/shotgun_icon_64.bmp";
	data->hud_textures[data->num_hud_textures++]
		= "assets/img/hud_shell.bmp";
}

/*
** Set animation file paths (and they also work as keys when queried from
** hash_table)
*/

void	sprite_animation_files_set(t_asset_files *data)
{
	data->sprite_files[data->num_sprites++]
		= "assets/animations/shotgun_anim_720p.bmp";
	data->sprite_files[data->num_sprites++]
		= "assets/animations/pistol_anim_720p.bmp";
	data->sprite_files[data->num_sprites++]
		= "assets/animations/fist_anim_720p.bmp";
	data->sprite_files[data->num_sprites++]
		= "assets/animations/rpg_anim_720p.bmp";
	data->sprite_files[data->num_sprites++]
		= "assets/animations/explosion1.bmp";
	data->sprite_files[data->num_sprites++]
		= "assets/animations/explosion2.bmp";
	data->sprite_files[data->num_sprites++]
		= "assets/animations/explosion3.bmp";
	data->sprite_files[data->num_sprites++]
		= "assets/animations/explosion4.bmp";
	data->sprite_files[data->num_sprites++] = "assets/animations/blood.bmp";
	data->sprite_files[data->num_sprites++]
		= "assets/animations/bullet_hole.bmp";
}

void	load_sprites_to_memory(t_assets *assets,
			t_asset_files *data)
{
	int32_t		i;
	t_surface	*animation_source;

	i = -1;
	while (++i < (int32_t)data->num_sprites)
	{
		animation_source = l3d_read_bmp_32bit_rgba_surface(
				assets->asset_files.sprite_files[i]);
		hash_map_add(assets->sprite_textures,
			(int64_t)assets->asset_files.sprite_files[i], animation_source);
	}
}

void	load_hud_textures_to_memory(t_assets *assets,
			t_asset_files *data)
{
	int32_t		i;
	t_surface	*hud_texture_source;

	i = -1;
	while (++i < (int32_t)data->num_hud_textures)
	{
		hud_texture_source = l3d_read_bmp_32bit_rgba_surface(
				assets->asset_files.hud_textures[i]);
		hash_map_add(assets->hud_textures,
			(int64_t)assets->asset_files.hud_textures[i], hud_texture_source);
	}
}
