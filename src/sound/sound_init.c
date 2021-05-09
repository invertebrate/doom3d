/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:51:15 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/25 18:16:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Initiating sound device for the first time
*/

t_mp	mix_init(t_doom3d *app, int channels)
{
	SDL_AudioSpec	cando;

	app->mp.channels = channels;
	ft_memset(&app->mp.auspec, 0, sizeof(app->mp.auspec));
	app->mp.auspec.freq = PREF_FREQ;
	app->mp.auspec.format = PREF_AUDIO;
	app->mp.auspec.channels = app->mp.channels;
	app->mp.auspec.samples = PREF_SAMPLES;
	app->mp.auspec.callback = mp_au_mix;
	app->mp.auspec.userdata = &app->mp;
	app->mp.audev = SDL_OpenAudioDevice(NULL, 0, &app->mp.auspec, &cando,
			SDL_AUDIO_ALLOW_ANY_CHANGE);
	if (app->mp.audev == 0)
		LOG_ERROR("Failed to open audio: %s", SDL_GetError());
	else
	{
		app->mp.auspec.format = cando.format;
		app->mp.auspec.freq = cando.freq;
		app->mp.auspec.channels = cando.channels;
		SDL_LockAudioDevice(app->mp.audev);
	}
	return (app->mp);
}

/*
** Store all the music into memory
*/

static int	mp_all_init(t_doom3d *app)
{
	int	i;

	mp_music_init(app);
	i = -1;
	while (++i < SOUNDS)
		if (!app->mp.library[i])
			return (-i);
	return (1);
}

/*
** Starting up music player
*/

void	mp_init(t_doom3d *app)
{
	int	ret;

	app->mp.channels = PREF_CHAN;
	app->mp.tracks = NULL;
	app->mp.effects = NULL;
	app->mp.st_vol = 1;
	app->mp.sf_vol = 1;
	app->mp = mix_init(app, app->mp.channels);
	ret = mp_all_init(app);
	if (ret != 1)
		error_check(true, "Failed to init sound");
	SDL_PauseAudioDevice(app->mp.audev, 0);
	SDL_UnlockAudioDevice(app->mp.audev);
	LOG_INFO("Audio status %d", SDL_GetAudioDeviceStatus(app->mp.audev));
}
