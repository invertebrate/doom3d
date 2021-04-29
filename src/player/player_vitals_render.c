/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_vitals_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:43:34 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/28 15:38:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	vitals_hp(t_doom3d *app)
{
	char		str[256];
	uint32_t	rgba[4];
	uint32_t	color;

	color = 0x00ff0000;
	l3d_u32_to_rgba(color, rgba);
	ft_memset(str, 0, sizeof(str));
	ft_sprintf(str, "HP: %.0f",
		(float)app->player.hp * 100.0 / (float)app->player.max_hp);
	window_text_render(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int[2]){20,
			app->window->framebuffer->height - 100},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->title_font);
}

static void	vitals_ammo(t_doom3d *app)
{
	char		str[256];
	uint32_t	rgba[4];
	uint32_t	color;

	color = 0xb08d5700;
	l3d_u32_to_rgba(color, rgba);
	ft_memset(str, 0, sizeof(str));
	ft_sprintf(str, "Ammo: %d | %d", app->player.equipped_weapon->clip, 
										app->player.equipped_weapon->ammo);
	window_text_render(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int[2]){200,
			app->window->framebuffer->height - 100},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->title_font);
}

static void	vitals_jetpack(t_doom3d *app)
{
	char		str[256];
	uint32_t	rgba[4];
	uint32_t	color;

	color = 0xFFD70000;
	l3d_u32_to_rgba(color, rgba);
	ft_memset(str, 0, sizeof(str));
	ft_sprintf(str, "JETPACK");
	window_text_render(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int[2]){app->window->framebuffer->width - 250,
			app->window->framebuffer->height - 100},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->title_font);
}

static void	vitals_keys(t_doom3d *app)
{
	char		str[256];
	uint32_t	rgba[4];
	uint32_t	color;

	color = 0xFFD70000;
	l3d_u32_to_rgba(color, rgba);
	ft_memset(str, 0, sizeof(str));
	ft_sprintf(str, "KEY");
	window_text_render(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int[2]){600,
			app->window->framebuffer->height - 200},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->title_font);
}

void	player_vitals_render(t_doom3d *app)
{
	int	i;

	vitals_hp(app);
	if (app->player.equipped_weapon->id != weapon_fist)
		vitals_ammo(app);
	if (app->player.can_fly)
		vitals_jetpack(app);
	i = -1;
	while (++i < MAX_KEYS)
	{
		if (app->player.keys[i])
			vitals_keys(app);
	}
}