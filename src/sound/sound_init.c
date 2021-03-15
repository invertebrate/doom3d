/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:51:15 by phakakos          #+#    #+#             */
/*   Updated: 2021/03/12 15:51:18 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Initiating sound device for the first time
*/

t_mp		mix_init(t_doom3d *app, int channels)
{
	SDL_AudioSpec	cando;

	app->mp.channels = channels;
	SDL_memset(&app->mp.auspec, 0, sizeof(app->mp.auspec));
	app->mp.auspec.freq = PREF_FREQ;
	app->mp.auspec.format = PREF_AUDIO;
	app->mp.auspec.channels = app->mp.channels;
	app->mp.auspec.samples = 4096;
	app->mp.auspec.callback = mp_au_mix;
	app->mp.auspec.userdata = &app->mp;

	app->mp.audev = SDL_OpenAudioDevice(NULL, 0, &app->mp.auspec, &cando,
		SDL_AUDIO_ALLOW_ANY_CHANGE);
	if (app->mp.audev == 0)
   		SDL_Log("Failed to open audio: %s", SDL_GetError());
	else
	{
		app->mp.auspec.format = cando.format;
		app->mp.auspec.freq = cando.freq;
		app->mp.auspec.channels = cando.channels;
		ft_printf("audev %d wanted %x got %x\n", app->mp.audev,
			PREF_AUDIO, cando.format);
		SDL_LockAudioDevice(app->mp.audev);
	}
	return (app->mp);
}

/*
** Store all sound effects into memory, and check that all sounds were loaded succesfully
*/

static int	mp_effect_init(t_doom3d *app, int i)
{
	app->mp.library[++i] = read_sound(EFFECT1, app);
	app->mp.library[++i] = read_sound(EFFECT2, app);
	i = -1;
	while (++i < SOUNDS)
		if (!app->mp.library[i])
			return (-i);
	return (1);
}

/*
** Store all the music into memory
*/

static int	mp_music_init(t_doom3d *app)
{
	int	i;

	i = -1;
	app->mp.library[++i] = read_sound(TRACK1, app);
	app->mp.library[++i] = read_sound(TRACK2, app);
	return (mp_effect_init(app, i));
}

/*
** Starting up music player
*/

void		mp_init(t_doom3d *app)
{
	int	ret;

	app->mp.channels = PREF_CHAN;
	app->mp.tracks = NULL;
	app->mp.effects = NULL;
	app->mp.st_vol = 1;
	app->mp.sf_vol = 1;
	app->mp = mix_init(app, app->mp.channels);
	if ((ret = mp_music_init(app)) != 1)
		ft_printf("Failed to init sound %d\n", -ret);
	SDL_PauseAudioDevice(app->mp.audev, 0);
	SDL_UnlockAudioDevice(app->mp.audev);
		//mp_print(&app->mp);
		ft_printf("audio status %d\n", SDL_GetAudioDeviceStatus(app->mp.audev));
}