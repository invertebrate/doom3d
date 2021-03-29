/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   media.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:24:39 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 16:25:48 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Play new sound effect. Returns 1 on success, 0 on fail
** ind == song library index t_sounds
** new is created by calling s_ini()
*/

int				handle_play_effect(t_doom3d *app, int ind, t_sound *new)
{
	//ind = ind < MUSIC ? MUSIC : ind;	// "SECURE" INDEXING?
	//ind = ind >= MUSIC + SEFFECT ? MUSIC + SEFFECT - 1 : ind;

	if (!new)
		return (0);
	new->sound = app->mp.library[ind];
	SDL_LockAudioDevice(app->mp.audev);
	mp_reorder(&app->mp.effects, new);
	SDL_UnlockAudioDevice(app->mp.audev);
	//sound_len(app->mp.effects);
	return (1);
}

/*
** Play new music. Returns 1 on success, 0 on fail
** ind == song library index t_sounds
** new is created by calling s_ini()
*/

int				handle_play_music(t_doom3d *app, int ind, t_sound *new)
{
	//ind = ind < 0 ? 0 : ind;	// "SECURE" INDEXING?
	//ind = ind >= MUSIC ? MUSIC - 1 : ind;
	if (!new)
		return (0);
	new->sound = app->mp.library[ind];
	SDL_LockAudioDevice(app->mp.audev);
	mp_reorder(&app->mp.tracks, new);
	SDL_UnlockAudioDevice(app->mp.audev);
	return (1);
}
