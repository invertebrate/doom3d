/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_effect_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:47:11 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/30 14:36:02 by ahakanen         ###   ########.fr       */
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
	mp_effect_init2(app);
}

void		mp_effect_init(t_doom3d *app)
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
	mp_effect_init1(app);
}
