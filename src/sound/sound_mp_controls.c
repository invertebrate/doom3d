/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_mp_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:51:41 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/24 16:33:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Swap channels. 1 MONO 2 STEREO 4 QUAD 6 5.1 AUDIO
*/

t_mp	mix_chan_swap(t_doom3d *app, int channels)
{
	SDL_LockAudioDevice(app->mp.audev);
	if (app->mp.auspec.channels == channels)
		return (app->mp);
	SDL_CloseAudioDevice(app->mp.audev);
	return (mix_init(app, channels));
}

/*
** Closing music player
*/

void	mp_close(t_doom3d *app)
{
	int		i;
	//t_sound	*curr;
	//t_sound	*next;


	mp_typec(app, 0, 0, SSTOPPED);
	LOG_INFO("Locking audio");
	SDL_LockAudioDevice(app->mp.audev);
	SDL_PauseAudioDevice(app->mp.audev, 1);
	LOG_INFO("Closing audio device %d", app->mp.audev);
	SDL_CloseAudioDevice(app->mp.audev);
	i = -1;
	LOG_INFO("Freeing audio library");
	while (++i < SOUNDS)
	{
		free(app->mp.library[i]->data);
		free(app->mp.library[i]);
		app->mp.library[i] = NULL;
	}
	/*curr = app->mp.tracks;
	LOG_INFO("Freeing music");
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	LOG_INFO("Freeing effects");
	curr = app->mp.effects;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}*/
	LOG_INFO("Audio closed");
}
