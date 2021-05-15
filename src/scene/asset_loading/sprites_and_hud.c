/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_and_hud.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:37:19 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 17:37:29 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	scene_hud_icon_files_set(t_asset_files *data)
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

void	scene_animation_sprite_files_set(t_asset_files *data)
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
	data->sprite_files[data->num_sprites++] = "assets/animations/bullet_hole.bmp";
}

void	load_sprites_to_memory(t_scene *scene,
			t_asset_files *data)
{
	int32_t		i;
	t_surface	*animation_source;

	i = -1;
	while (++i < (int32_t)data->num_sprites)
	{
		animation_source = l3d_read_bmp_32bit_rgba_surface(
				scene->asset_files.sprite_files[i]);
		hash_map_add(scene->sprite_textures,
			(int64_t)scene->asset_files.sprite_files[i], animation_source);
	}
}

void	load_hud_textures_to_memory(t_scene *scene,
			t_asset_files *data)
{
	int32_t		i;
	t_surface	*hud_texture_source;

	i = -1;
	while (++i < (int32_t)data->num_hud_textures)
	{
		hud_texture_source = l3d_read_bmp_32bit_rgba_surface(
				scene->asset_files.hud_textures[i]);
		hash_map_add(scene->hud_textures,
			(int64_t)scene->asset_files.hud_textures[i], hud_texture_source);
	}
}
