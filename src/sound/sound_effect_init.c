/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_effect_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:47:11 by phakakos          #+#    #+#             */
/*   Updated: 2021/05/07 13:49:53 by sotamursu        ###   ########.fr       */
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
	app->mp.library[sf_audio_log_1] = read_sound(SF_AUDIO_LOG_1, app);
	app->mp.library[sf_audio_log_2] = read_sound(SF_AUDIO_LOG_2, app);
	app->mp.library[sf_audio_log_3] = read_sound(SF_AUDIO_LOG_3, app);
	app->mp.library[sf_audio_log_4] = read_sound(SF_AUDIO_LOG_4, app);
	app->mp.library[sf_audio_log_5] = read_sound(SF_AUDIO_LOG_5, app);
	app->mp.library[sf_audio_log_6] = read_sound(SF_AUDIO_LOG_6, app);
	app->mp.library[sf_audio_log_7] = read_sound(SF_AUDIO_LOG_7, app);
	app->mp.library[sf_audio_log_8] = read_sound(SF_AUDIO_LOG_8, app);
	app->mp.library[sf_audio_log_9] = read_sound(SF_AUDIO_LOG_9, app);
	app->mp.library[sf_audio_log_10] = read_sound(SF_AUDIO_LOG_10, app);
	app->mp.library[sf_audio_log_11] = read_sound(SF_AUDIO_LOG_11, app);
	app->mp.library[sf_audio_log_12] = read_sound(SF_AUDIO_LOG_12, app);
	app->mp.library[sf_audio_log_13] = read_sound(SF_AUDIO_LOG_13, app);
	app->mp.library[sf_audio_log_14] = read_sound(SF_AUDIO_LOG_14, app);
	app->mp.library[sf_audio_log_15] = read_sound(SF_AUDIO_LOG_15, app);
	app->mp.library[sf_audio_log_16] = read_sound(SF_AUDIO_LOG_16, app);
	app->mp.library[sf_audio_log_17] = read_sound(SF_AUDIO_LOG_17, app);
	app->mp.library[sf_audio_log_18] = read_sound(SF_AUDIO_LOG_18, app);
	app->mp.library[sf_audio_log_19] = read_sound(SF_AUDIO_LOG_19, app);
	app->mp.library[sf_audio_log_20] = read_sound(SF_AUDIO_LOG_20, app);
	mp_effect_init2(app);
}

void	mp_effect_init(t_doom3d *app)
{
	app->mp.library[sf_shtg_fire] = read_sound(SF_SHTG_FIRE, app);
	app->mp.library[sf_explsion] = read_sound(SF_EXPLSION, app);
	app->mp.library[sf_pstl_fire] = read_sound(SF_PSTL_FIRE, app);
	app->mp.library[sf_gun_empt] = read_sound(SF_GUN_EMPT, app);
	app->mp.library[sf_gun_rel] = read_sound(SF_GUN_REL, app);
	app->mp.library[sf_rpg_fire] = read_sound(SF_RPG_FIRE, app);
	app->mp.library[sf_fist_fire] = read_sound(SF_FIST_FIRE, app);
	app->mp.library[sf_fist_hit] = read_sound(SF_FIST_HIT, app);
	app->mp.library[sf_explsion2] = read_sound(SF_EXPLSION2, app);
	app->mp.library[sf_landing] = read_sound(SF_LANDING, app);
	app->mp.library[sf_pickup] = read_sound(SF_PICKUP, app);
	app->mp.library[sf_door_locked] = read_sound(SF_DOOR_LOCKED, app);
	app->mp.library[sf_door_open] = read_sound(SF_DOOR_OPEN, app);
	app->mp.library[sf_monster_hurt] = read_sound(SF_MONSTER_HURT, app);
	app->mp.library[sf_monster_alert] = read_sound(SF_MONSTER_ALERT, app);
	app->mp.library[sf_monster_shoot] = read_sound(SF_MONSTER_SHOOT, app);
	app->mp.library[sf_player_hurt] = read_sound(SF_PLAYER_HURT, app);
	app->mp.library[sf_crate_break] = read_sound(SF_CRATE_BREAK, app);
	app->mp.library[sf_spawn] = read_sound(SF_SPAWN, app);
	app->mp.library[sf_glass] = read_sound(SF_GLASS, app);
	mp_effect_init1(app);
}
