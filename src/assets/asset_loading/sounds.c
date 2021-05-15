/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 21:52:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 22:07:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	sounds_load_sub(t_assets *assets)
{
	assets->sounds[sf_shtg_fire] = sdl_asset_as_memory(SF_SHTG_FIRE);
	assets->sounds[sf_explsion] = sdl_asset_as_memory(SF_EXPLSION);
	assets->sounds[sf_pstl_fire] = sdl_asset_as_memory(SF_PSTL_FIRE);
	assets->sounds[sf_gun_empt] = sdl_asset_as_memory(SF_GUN_EMPT);
	assets->sounds[sf_gun_rel] = sdl_asset_as_memory(SF_GUN_REL);
	assets->sounds[sf_rpg_fire] = sdl_asset_as_memory(SF_RPG_FIRE);
	assets->sounds[sf_fist_fire] = sdl_asset_as_memory(SF_FIST_FIRE);
	assets->sounds[sf_fist_hit] = sdl_asset_as_memory(SF_FIST_HIT);
	assets->sounds[sf_explsion2] = sdl_asset_as_memory(SF_EXPLSION2);
	assets->sounds[sf_landing] = sdl_asset_as_memory(SF_LANDING);
	assets->sounds[sf_pickup] = sdl_asset_as_memory(SF_PICKUP);
	assets->sounds[sf_door_locked] = sdl_asset_as_memory(SF_DOOR_LOCKED);
	assets->sounds[sf_door_open] = sdl_asset_as_memory(SF_DOOR_OPEN);
	assets->sounds[sf_monster_hurt] = sdl_asset_as_memory(SF_MONSTER_HURT);
	assets->sounds[sf_monster_alert] = sdl_asset_as_memory(SF_MONSTER_ALERT);
	assets->sounds[sf_monster_shoot] = sdl_asset_as_memory(SF_MONSTER_SHOOT);
	assets->sounds[sf_player_hurt] = sdl_asset_as_memory(SF_PLAYER_HURT);
	assets->sounds[sf_crate_break] = sdl_asset_as_memory(SF_CRATE_BREAK);
	assets->sounds[sf_spawn] = sdl_asset_as_memory(SF_SPAWN);
}

void	sounds_load(t_assets *assets)
{
	assets->sounds[mu_main] = sdl_asset_as_memory(TRACK1);
	assets->sounds[mu_doom] = sdl_asset_as_memory(TRACK2);
	assets->sounds[sf_audio_log_1] = sdl_asset_as_memory(SF_AUDIO_LOG_1);
	assets->sounds[sf_audio_log_2] = sdl_asset_as_memory(SF_AUDIO_LOG_2);
	assets->sounds[sf_audio_log_3] = sdl_asset_as_memory(SF_AUDIO_LOG_3);
	assets->sounds[sf_audio_log_4] = sdl_asset_as_memory(SF_AUDIO_LOG_4);
	assets->sounds[sf_audio_log_5] = sdl_asset_as_memory(SF_AUDIO_LOG_5);
	assets->sounds[sf_audio_log_6] = sdl_asset_as_memory(SF_AUDIO_LOG_6);
	assets->sounds[sf_audio_log_7] = sdl_asset_as_memory(SF_AUDIO_LOG_7);
	assets->sounds[sf_audio_log_8] = sdl_asset_as_memory(SF_AUDIO_LOG_8);
	assets->sounds[sf_audio_log_9] = sdl_asset_as_memory(SF_AUDIO_LOG_9);
	assets->sounds[sf_audio_log_10] = sdl_asset_as_memory(SF_AUDIO_LOG_10);
	assets->sounds[sf_audio_log_11] = sdl_asset_as_memory(SF_AUDIO_LOG_11);
	assets->sounds[sf_audio_log_12] = sdl_asset_as_memory(SF_AUDIO_LOG_12);
	assets->sounds[sf_audio_log_13] = sdl_asset_as_memory(SF_AUDIO_LOG_13);
	assets->sounds[sf_audio_log_14] = sdl_asset_as_memory(SF_AUDIO_LOG_14);
	assets->sounds[sf_audio_log_15] = sdl_asset_as_memory(SF_AUDIO_LOG_15);
	assets->sounds[sf_audio_log_16] = sdl_asset_as_memory(SF_AUDIO_LOG_16);
	assets->sounds[sf_audio_log_17] = sdl_asset_as_memory(SF_AUDIO_LOG_17);
	assets->sounds[sf_audio_log_18] = sdl_asset_as_memory(SF_AUDIO_LOG_18);
	assets->sounds[sf_audio_log_19] = sdl_asset_as_memory(SF_AUDIO_LOG_19);
	assets->sounds[sf_audio_log_20] = sdl_asset_as_memory(SF_AUDIO_LOG_20);
}

void	sounds_destroy(t_assets *assets)
{
	int32_t	i;

	i = -1;
	while (++i < NUM_SOUNDS)
		free(assets->sounds[i]);
}
