/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_effect_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:47:11 by phakakos          #+#    #+#             */
/*   Updated: 2021/05/17 23:42:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	mp_effect_init4(t_doom3d *app)
{
	if (app)
		return ;
}

static void	mp_effect_init3(t_doom3d *app)
{
	mp_effect_init4(app);
}

static void	mp_effect_init2(t_doom3d *app)
{
	mp_effect_init3(app);
}

static void	mp_effect_init1(t_doom3d *app)
{
	app->mp.library[sf_audio_log_1] = read_sound(sf_audio_log_1, app);
	app->mp.library[sf_audio_log_2] = read_sound(sf_audio_log_2, app);
	app->mp.library[sf_audio_log_3] = read_sound(sf_audio_log_3, app);
	app->mp.library[sf_audio_log_4] = read_sound(sf_audio_log_4, app);
	app->mp.library[sf_audio_log_5] = read_sound(sf_audio_log_5, app);
	app->mp.library[sf_audio_log_6] = read_sound(sf_audio_log_6, app);
	app->mp.library[sf_audio_log_7] = read_sound(sf_audio_log_7, app);
	app->mp.library[sf_audio_log_8] = read_sound(sf_audio_log_8, app);
	app->mp.library[sf_audio_log_9] = read_sound(sf_audio_log_9, app);
	app->mp.library[sf_audio_log_10] = read_sound(sf_audio_log_10, app);
	app->mp.library[sf_audio_log_11] = read_sound(sf_audio_log_11, app);
	app->mp.library[sf_audio_log_12] = read_sound(sf_audio_log_12, app);
	app->mp.library[sf_audio_log_13] = read_sound(sf_audio_log_13, app);
	app->mp.library[sf_audio_log_14] = read_sound(sf_audio_log_14, app);
	app->mp.library[sf_audio_log_15] = read_sound(sf_audio_log_15, app);
	app->mp.library[sf_audio_log_16] = read_sound(sf_audio_log_16, app);
	app->mp.library[sf_audio_log_17] = read_sound(sf_audio_log_17, app);
	app->mp.library[sf_audio_log_18] = read_sound(sf_audio_log_18, app);
	app->mp.library[sf_audio_log_19] = read_sound(sf_audio_log_19, app);
	app->mp.library[sf_audio_log_20] = read_sound(sf_audio_log_20, app);
	mp_effect_init2(app);
}

void	mp_effect_init(t_doom3d *app)
{
	app->mp.library[sf_shtg_fire] = read_sound(sf_shtg_fire, app);
	app->mp.library[sf_explsion] = read_sound(sf_explsion, app);
	app->mp.library[sf_pstl_fire] = read_sound(sf_pstl_fire, app);
	app->mp.library[sf_gun_empt] = read_sound(sf_gun_empt, app);
	app->mp.library[sf_gun_rel] = read_sound(sf_gun_rel, app);
	app->mp.library[sf_rpg_fire] = read_sound(sf_rpg_fire, app);
	app->mp.library[sf_fist_fire] = read_sound(sf_fist_fire, app);
	app->mp.library[sf_fist_hit] = read_sound(sf_fist_hit, app);
	app->mp.library[sf_explsion2] = read_sound(sf_explsion2, app);
	app->mp.library[sf_landing] = read_sound(sf_landing, app);
	app->mp.library[sf_pickup] = read_sound(sf_pickup, app);
	app->mp.library[sf_door_locked] = read_sound(sf_door_locked, app);
	app->mp.library[sf_door_open] = read_sound(sf_door_open, app);
	app->mp.library[sf_monster_hurt] = read_sound(sf_monster_hurt, app);
	app->mp.library[sf_monster_alert] = read_sound(sf_monster_alert, app);
	app->mp.library[sf_monster_shoot] = read_sound(sf_monster_shoot, app);
	app->mp.library[sf_player_hurt] = read_sound(sf_player_hurt, app);
	app->mp.library[sf_crate_break] = read_sound(sf_crate_break, app);
	app->mp.library[sf_spawn] = read_sound(sf_spawn, app);
	app->mp.library[sf_glass] = read_sound(sf_glass, app);
	mp_effect_init1(app);
}
