/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:37:19 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 19:58:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Set animation file paths (and they also work as keys when queried from
** hash_table)
*/

void			scene_animation_sprite_files_set(t_asset_files *data)
{
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/shotgun_anim_1080p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/pistol_anim_1080p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/fist_anim_1080p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/rpg_anim_1080p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/shotgun_anim_720p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/pistol_anim_720p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/fist_anim_720p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/rpg_anim_720p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/shotgun_anim_540p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/pistol_anim_540p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/fist_anim_540p.bmp";
	data->animation_sprite_files[data->num_animations_sprite++] =
		"assets/animations/rpg_anim_540p.bmp";
}

void			load_sprite_animations_to_memory(t_scene *scene,
					t_asset_files *data)
{
	int32_t		i;
	t_surface	*animation_source;
	t_surface	*scaled_anim_source;

	i = -1;
	while (++i < (int32_t)data->num_animations_sprite)
	{
		animation_source = l3d_read_bmp_32bit_rgba_surface(
				scene->asset_files.animation_sprite_files[i]);
		scaled_anim_source = l3d_image_scaled(animation_source,
			animation_source->w * ANIMATION_SCALE, animation_source->h *
				ANIMATION_SCALE);
		free(animation_source->pixels);
		free(animation_source);
		hash_map_add(scene->animation_textures,
			(int64_t)scene->asset_files.animation_sprite_files[i],
			scaled_anim_source);
	}
}
