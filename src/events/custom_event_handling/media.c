/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   media.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:24:39 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:26:41 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Play new sound effect. Returns 1 on success, 0 on fail
** ind == song library index t_sounds
** new is created by calling s_ini()
*/

int	handle_play_effect(t_doom3d *app, int ind, t_sound *new)
{
	if (!new)
		return (0);
	new->sound = app->mp.library[ind];
	SDL_LockAudioDevice(app->mp.audev);
	mp_reorder(&app->mp.effects, new, NULL);
	SDL_UnlockAudioDevice(app->mp.audev);
	return (1);
}

/*
** Play new music. Returns 1 on success, 0 on fail
** ind == song library index t_sounds
** new is created by calling s_ini()
*/

int	handle_play_music(t_doom3d *app, int ind, t_sound *new)
{
	if (!new)
		return (0);
	new->sound = app->mp.library[ind];
	SDL_LockAudioDevice(app->mp.audev);
	mp_reorder(&app->mp.tracks, new, NULL);
	SDL_UnlockAudioDevice(app->mp.audev);
	return (1);
}
