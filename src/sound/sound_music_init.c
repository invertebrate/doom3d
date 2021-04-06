/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_music_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:47:03 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/06 17:47:05 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	mp_music_init4(t_doom3d *app)
{
	mp_effect_init(app);
}

static void	mp_music_init3(t_doom3d *app)
{
	mp_music_init4(app);
}

static void	mp_music_init2(t_doom3d *app)
{
	mp_music_init3(app);
}

static void	mp_music_init1(t_doom3d *app)
{
	mp_music_init2(app);
}

void		mp_music_init(t_doom3d *app)
{
	app->mp.library[mu_main] = read_sound(TRACK1, app);
	app->mp.library[mu_doom] = read_sound(TRACK2, app);
	mp_music_init1(app);
}
