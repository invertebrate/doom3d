/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_effect_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:47:11 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/06 17:47:12 by phakakos         ###   ########.fr       */
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
	mp_effect_init1(app);
}
