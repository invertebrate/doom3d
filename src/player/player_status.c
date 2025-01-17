/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:53:53 by ahakanen          #+#    #+#             */
/*   Updated: 2021/06/01 01:30:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_onhit(t_doom3d *app, int damage)
{
	float	vol;

	if (app->settings.is_hard)
		damage = damage * 2;
	app->player.hp -= damage;
	app->stats.damage_taken += damage;
	vol = (float)(damage) / (app->player.max_hp * 0.02f);
	if (vol > 1)
		vol = 1;
	push_custom_event(app,
		event_effect_play, (void*)sf_player_hurt, s_ini(0, 1, st_game, vol));
	if (app->player.hp <= 0 && !app->player.is_dead)
	{
		push_custom_event(app, event_scene_change,
			(void *)scene_id_main_menu, NULL);
		notify_user(app, (t_notification){.message = "You died",
			.time = 6000, .type = notification_type_layer});
		app->stats.total_deaths++;
		app->player.is_dead = true;
	}
}

void	player_splash_damage(t_doom3d *app, t_3d_object *projectile_obj)
{
	float			mag;
	int				damage;
	t_vec3			dist;
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	ml_vector3_sub(projectile_obj->aabb.center, app->player.aabb.center, dist);
	mag = ml_vector3_mag(dist);
	if (mag < projectile->radius)
	{
		damage = projectile->damage * (1 - (mag / projectile->radius));
		player_onhit(app, damage);
	}
}
