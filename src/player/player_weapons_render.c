/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_weapons_render.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:03:10 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/06 16:10:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static float	weapon_blend(t_doom3d *app, t_weapon_id weapon)
{
	if (app->player.equipped_weapon->id == weapon)
		return (1.0);
	return (0.5);
}

static void	render_pistol(t_doom3d *app)
{
	t_surface	*weapon;

	weapon = hash_map_get(app->active_scene->hud_textures,
			(int64_t)"assets/img/pistol_icon_64.bmp");
	error_check(!weapon, "Could not find pistol_icon_64 image");
	l3d_image_place(&(t_surface){.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer}, weapon,
		(int32_t[2]){app->window->framebuffer->width - 96 - 4 * 74 - 64,
		app->window->framebuffer->height - 76},
		weapon_blend(app, weapon_pistol));
}

void	weapons_render(t_doom3d *app)
{
	t_surface	*weapon;

	render_pistol(app);
	weapon = hash_map_get(app->active_scene->hud_textures,
			(int64_t)"assets/img/shotgun_icon_64.bmp");
	error_check(!weapon, "Could not find shotgun_icon_64 image");
	l3d_image_place(&(t_surface){.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer}, weapon,
		(int32_t[2]){app->window->framebuffer->width - 96 - 3 * 74 - 64,
		app->window->framebuffer->height - 76},
		weapon_blend(app, weapon_shotgun));
	weapon = hash_map_get(app->active_scene->hud_textures,
			(int64_t)"assets/img/rpg_icon_64.bmp");
	error_check(!weapon, "Could not find rpg_icon_64 image");
	l3d_image_place(&(t_surface){.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer}, weapon,
		(int32_t[2]){app->window->framebuffer->width - 96 - 2 * 74 - 64,
		app->window->framebuffer->height - 76}, weapon_blend(app, weapon_rpg));
}
