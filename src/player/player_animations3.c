/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animations3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:28:46 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 17:35:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** This function is called in `src/render/player_hud.c` in
** `player_animation_render` and it determines which source image is used
** for animation based on equipped weapon
*/

t_surface	*get_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return ((t_surface *)hash_map_get(app->active_scene->sprite_textures,
				(long int)"assets/animations/shotgun_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_pistol)
		return ((t_surface *)hash_map_get(app->active_scene->sprite_textures,
				(long int)"assets/animations/pistol_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_fist)
		return ((t_surface *)hash_map_get(app->active_scene->sprite_textures,
				(long int)"assets/animations/fist_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_rpg)
	{
		return ((t_surface *)hash_map_get(app->active_scene->sprite_textures,
				(long int)"assets/animations/rpg_anim_720p.bmp"));
	}
	return (NULL);
}
