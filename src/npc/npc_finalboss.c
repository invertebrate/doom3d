/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_finalboss.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/06/01 00:24:28 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	set_attack_pattern3(t_npc *npc, int i)
{
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_spawn_b;
	npc->atk_pattern[i++] = action_repeat;
}

static void	set_attack_pattern2(t_npc *npc, int i)
{
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_spawn_a;
	npc->atk_pattern[i++] = action_spawn_a;
	npc->atk_pattern[i++] = action_spawn_a;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_melee_basic;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_melee_basic;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_melee_basic;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	set_attack_pattern3(npc, i);
}

static void	set_attack_pattern(t_npc *npc)
{
	int	i;

	i = 0;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_melee_basic;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_melee_basic;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_melee_basic;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_projectile_rpg;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	npc->atk_pattern[i++] = action_wait;
	set_attack_pattern2(npc, i);
}

void	npc_boss(t_doom3d *app, t_npc *npc, int type)
{
	if (type == npc_type_boss)
	{
		npc->type = type;
		npc->model_key = MONSTER01_MODEL;
		npc->texture_key = "assets/textures/monster01_finalboss.bmp";
		npc->normal_map_key = MONSTER01_NORMM;
		npc->model_scale = 0.05;
		npc->hp = 10000;
		npc->speed = app->unit_size / 4.2;
		npc->atk_range = app->unit_size * 12;
		npc->atk_dmg = 250;
		npc->advance = false;
		npc->max_interest = 1000000000;
		set_attack_pattern(npc);
	}
}

void	npc_boss_death(t_doom3d *app)
{
	int		min;
	int		s;

	push_custom_event(app,
		event_effect_play, (void *)sf_audio_log_20, s_ini(0, 1, st_game, 1.0));
	show_subtitle(app, sf_audio_log_20);
	trigger_timer_start(app, NULL, timer_end, 20000);
	app->stats.level_end_time = SDL_GetTicks();
	app->stats.completion_time += (app->stats.level_end_time
			- app->stats.level_start_time) / 1000;
	s = app->stats.completion_time % 60;
	min = app->stats.completion_time / 60;
	ft_memset(app->stats.stats_text, 0, sizeof(app->stats.stats_text));
	ft_sprintf(app->stats.stats_text,
		"Completion Time: %d min %d s\nTotal Damage Dealt: %d\n"
		"Total Kills: %d\nShots Fired: %d\nTotal Deaths: %d\n",
		min, s, app->stats.total_damage, app->stats.total_kills,
		app->stats.shots_fired, app->stats.total_deaths);
	notify_user(app, (t_notification){
		. message = app->stats.stats_text, .time = 20000,
		.type = notification_type_layer});
}
