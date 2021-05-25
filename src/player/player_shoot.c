/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:51:46 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/25 18:37:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	player_shoots(t_doom3d *app)
{
	t_vec3			origin;
	t_vec3			add;

	if (app->player.equipped_weapon->id != weapon_fist)
		check_npc_hearing(app, app->player.aabb.center);
	ml_vector3_mul(app->player.forward, NEAR_CLIP_DIST, add);
	ml_vector3_add(app->player.pos, add, origin);
	if (app->player.equipped_weapon->id == weapon_fist
		|| app->player.equipped_weapon->id == weapon_pistol)
		player_shoot_ray(app, origin, app->player.forward);
	else if (app->player.equipped_weapon->id == weapon_rpg)
		push_custom_event(app, event_player_shoot_projectile, NULL, NULL);
	else if (app->player.equipped_weapon->id == weapon_shotgun)
		shoot_shotgun(app, origin, 0);
	if (app->player.equipped_weapon->id != weapon_fist)
	{
		app->player.equipped_weapon->clip--;
		app->player.equipped_weapon->ammo--;
	}
}

/*
** 	Clicking shoots right away. Else, fired according to fire rate
*/

void	player_shoot(t_doom3d *app, uint32_t curr_time)
{
	static uint32_t	prev_shot_time;
	static uint32_t	prev_shot_weapon_id;

	if (prev_shot_weapon_id == app->player.equipped_weapon->id)
	{
		if (prev_shot_time != 0 && (float)(curr_time - prev_shot_time) / 1000.0
			< (1.0 / app->player.equipped_weapon->fire_rate))
			return ;
	}
	if (app->player.equipped_weapon->clip > 0)
		set_player_shoot_frame(app);
	else if (app->player.equipped_weapon->clip == 0)
	{
		if (app->settings.is_debug)
			LOG_DEBUG("Out of Ammo");
		set_player_default_frame(app);
		push_custom_event(app,
			event_effect_play, (void*)sf_gun_empt, s_ini(0, 1, st_game, 1.0));
		return ;
	}
	prev_shot_time = SDL_GetTicks();
	player_shoots(app);
	prev_shot_weapon_id = app->player.equipped_weapon->id;
}
