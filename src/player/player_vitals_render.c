/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vitals_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:43:34 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/15 22:21:48 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	hp_render(t_doom3d *app)
{
	char		str[256];
	uint32_t	rgba[4];
	uint32_t	color;
	t_surface	*hp_image;

	color = 0x00ff0000;
	l3d_u32_to_rgba(color, rgba);
	ft_memset(str, 0, sizeof(str));
	ft_sprintf(str, "%.0f",
		(float)app->player.hp * 100.0 / (float)app->player.max_hp);
	window_text_render_centered(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int [2]){96 + 48 + 1 * 74,
		app->window->framebuffer->height - 35},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->main_font);
	hp_image = hash_map_get(app->assets.hud_textures,
			(int64_t)"assets/img/health_icon_64.bmp");
	error_check(!hp_image, "Could not find hp_image image");
	l3d_image_place(&(t_surface){
		.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer},
		hp_image,
		(int32_t[2]){96, app->window->framebuffer->height - 76}, 1.0);
}

static void	ammo_render(t_doom3d *app)
{
	char		str[256];
	uint32_t	rgba[4];
	uint32_t	color;
	t_surface	*ammo_image;

	color = 0xb08d5700;
	l3d_u32_to_rgba(color, rgba);
	ft_memset(str, 0, sizeof(str));
	ft_sprintf(str, "%d | %d", app->player.equipped_weapon->clip,
		app->player.equipped_weapon->ammo);
	window_text_render_centered(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int [2]){96 + 96 + 3 * 74,
		app->window->framebuffer->height - 35},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->main_font);
	ammo_image = hash_map_get(app->assets.hud_textures,
			(int64_t)"assets/img/ammo_icon_64.bmp");
	error_check(!ammo_image, "Could not find ammo_image image");
	l3d_image_place(&(t_surface){
		.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer},
		ammo_image, (int32_t[2]){96 + 42 + 2 * 74,
		app->window->framebuffer->height - 76}, 1.0);
}

static void	jetpack_render(t_doom3d *app)
{
	t_surface	*jetpack_image;
	float		blend_val;

	blend_val = 0.5;
	if (app->player.can_fly)
		blend_val = 1.0;
	jetpack_image = hash_map_get(app->assets.hud_textures,
			(int64_t)"assets/img/jetpack_icon_64.bmp");
	error_check(!jetpack_image, "Could not find jetpack_image image");
	l3d_image_place(&(t_surface){
		.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer},
		jetpack_image,
		(int32_t[2]){app->window->framebuffer->width - 96 - 1 * 74 - 64,
		app->window->framebuffer->height - 76}, blend_val);
}

static void	keys_render(t_doom3d *app)
{
	t_surface	*key_image;
	float		blend_val;
	int32_t		i;

	blend_val = 0.5;
	i = -1;
	while (++i < MAX_KEYS)
	{
		if (app->player.keys[i])
		{
			blend_val = 1.0;
			break ;
		}
	}
	key_image = hash_map_get(app->assets.hud_textures,
			(int64_t)"assets/img/keycard_icon_64.bmp");
	error_check(!key_image, "Could not find key_image image");
	l3d_image_place(&(t_surface){
		.h = app->window->framebuffer->height,
		.w = app->window->framebuffer->width,
		.pixels = app->window->framebuffer->buffer},
		key_image,
		(int32_t[2]){app->window->framebuffer->width - 96 - 64,
		app->window->framebuffer->height - 76}, blend_val);
}

void	player_stats_render(t_doom3d *app)
{
	hp_render(app);
	if (app->player.equipped_weapon->id != weapon_fist)
		ammo_render(app);
	jetpack_render(app);
	weapons_render(app);
	keys_render(app);
}
