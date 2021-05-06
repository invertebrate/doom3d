/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:37:19 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/06 14:38:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	scene_hud_icon_files_set(t_asset_files *data)
{
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/img/ammo_icon_64.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/img/jetpack_icon_64.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/img/pistol_icon_64.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/img/rpg_icon_64.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/img/health_icon_64.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/img/keycard_icon_64.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/img/shotgun_icon_64.bmp";
}

/*
** Set animation file paths (and they also work as keys when queried from
** hash_table)
*/

void	scene_animation_sprite_files_set(t_asset_files *data)
{
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/shotgun_anim_1080p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/pistol_anim_1080p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/fist_anim_1080p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/rpg_anim_1080p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/shotgun_anim_720p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/pistol_anim_720p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/fist_anim_720p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/rpg_anim_720p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/shotgun_anim_540p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/pistol_anim_540p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/fist_anim_540p.bmp";
	data->hud_sprite_files[data->num_hud_sprites++]
		= "assets/animations/rpg_anim_540p.bmp";
	scene_hud_icon_files_set(data);
}

void	load_sprites_to_memory(t_scene *scene,
			t_asset_files *data)
{
	int32_t		i;
	t_surface	*animation_source;
	t_surface	*scaled_anim_source;

	i = -1;
	while (++i < (int32_t)data->num_hud_sprites)
	{
		animation_source = l3d_read_bmp_32bit_rgba_surface(
				scene->asset_files.hud_sprite_files[i]);
		if (ft_match((char*)scene->asset_files.hud_sprite_files[i],
			"assets/anim*"))
		{
			scaled_anim_source = l3d_image_scaled(animation_source,
				animation_source->w * ANIMATION_SCALE,
				animation_source->h * ANIMATION_SCALE);
			free(animation_source->pixels);
			free(animation_source);
		}
		else
			scaled_anim_source = animation_source;
		hash_map_add(scene->hud_textures,
			(int64_t)scene->asset_files.hud_sprite_files[i],
			scaled_anim_source);
	}
}
