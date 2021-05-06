/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animations3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:28:46 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/06 14:20:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_surface	*get_1080p_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/shotgun_anim_1080p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_pistol)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/pistol_anim_1080p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_fist)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/fist_anim_1080p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_rpg)
	{
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/rpg_anim_1080p.bmp"));
	}
	return (NULL);
}

static t_surface	*get_720p_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/shotgun_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_pistol)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/pistol_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_fist)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/fist_anim_720p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_rpg)
	{
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/rpg_anim_720p.bmp"));
	}
	return (NULL);
}

static t_surface	*get_540p_animation_source(t_doom3d *app)
{
	if (app->player.equipped_weapon->id == weapon_shotgun)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/shotgun_anim_540p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_pistol)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/pistol_anim_540p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_fist)
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/fist_anim_540p.bmp"));
	else if (app->player.equipped_weapon->id == weapon_rpg)
	{
		return ((t_surface *)hash_map_get(app->active_scene->hud_textures,
				(long int)"assets/animations/rpg_anim_540p.bmp"));
	}
	return (NULL);
}

/*
** This function is called in `src/render/player_hud.c` in
** `player_animation_render` and it determines which source image is used
** for animation based on equipped weapon
*/

t_surface	*get_animation_source(t_doom3d *app)
{
	if (app->settings.height == 1080)
	{
		return (get_1080p_animation_source(app));
	}
	else if (app->settings.height == 720)
	{
		return (get_720p_animation_source(app));
	}
	else if (app->settings.height == 540)
	{
		return (get_540p_animation_source(app));
	}
	return (NULL);
}
