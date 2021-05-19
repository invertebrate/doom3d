/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:51:05 by phakakos          #+#    #+#             */
/*   Updated: 2021/05/19 18:22:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Reading WAV-files into t_track struct
*/

t_track	*read_sound(t_sounds sound, t_doom3d *app)
{
	t_track			*ret;
	SDL_AudioSpec	wave;
	Uint8			*data;
	Uint32			dlen;
	SDL_AudioCVT	cvt;

	error_check(!SDL_LoadWAV_RW(SDL_RWFromConstMem(app->assets.sounds[sound].data,
				app->assets.sounds[sound].size), 1, &wave, &data, &dlen),
		"Could not load sound");
	if (SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,
			app->mp.auspec.format, app->mp.auspec.channels, app->mp.auspec.freq)
		== -1)
		return (NULL);
	error_check(!(cvt.buf = (Uint8 *)ft_calloc(dlen * cvt.len_mult)),
		"Failed to alloc cvt.buf");
	ft_memcpy(cvt.buf, data, dlen);
	cvt.len = dlen;
	SDL_ConvertAudio(&cvt);
	SDL_FreeWAV(data);
	error_check(!(ret = (t_track *)ft_calloc(sizeof(t_track))), "E:Alloc trak");
	ret->data = cvt.buf;
	ret->len = cvt.len_cvt;
	return (ret);
}

/*
** Create a new sound struct
** loop == TRUE/FALSE 1/0
** priorioty == higher is mixed first
** type == t_sound_types
** vol = 1 - 0
*/

t_sound	*s_ini(char loop, char priority, char type, float vol)
{
	t_sound	*ret;

	ret = (t_sound *)malloc(sizeof(t_sound));
	if (!ret)
		return (NULL);
	ret->pos = 0;
	ret->state = SPLAYING;
	ret->type = type;
	ret->loop = loop;
	ret->vol = vol;
	ret->priority = priority;
	ret->next = NULL;
	return (ret);
}

/*
** Calculate distance mag in one function for distance volume distance
*/

float	sound_mag(t_vec3 v1, t_vec3 v2)
{
	t_vec3	sub;

	ml_vector3_sub(v1, v2, sub);
	return (ml_vector3_mag(sub));
}

/*
** Scale sound volume based on the call distance from player
** vol_max = max volume 0-1
** dist = distance from player (using ml_vector3_mag())
** mdist = max distance from the sound. If -1 will use SOUND_DIST instead
*/

float	distance_vol(float vol_max, float dist, float mdist)
{
	float	max_dist;
	float	ret;

	max_dist = SOUND_DIST;
	if (mdist != -1)
		max_dist = mdist;
	if (vol_max > 1.0f)
		vol_max = 1.0f;
	else if (vol_max < 0.0f)
		vol_max = 0;
	if (dist >= max_dist || (!max_dist && dist) || !vol_max)
		return (0.0f);
	else if (!max_dist && !dist)
		return (vol_max);
	ret = vol_max * (1 - dist / max_dist);
	if (ret > 1)
		return (1);
	return (ret);
}
