/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:51:05 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/25 18:13:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Reading WAV-files into t_track struct
*/

t_track			*read_sound(char *file, t_doom3d *app)
{
	t_track			*ret;
	SDL_AudioSpec	wave;
	Uint8			*data;
	Uint32			dlen;
	SDL_AudioCVT	cvt;

	if (SDL_LoadWAV(file, &wave, &data, &dlen) == NULL)
	{
		LOG_ERROR("Couldn't load %s: %s\n", file, SDL_GetError());
		return (NULL);
	}
	if (SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,
		app->mp.auspec.format, app->mp.auspec.channels, app->mp.auspec.freq)
		== -1)
		return (NULL);
	error_check(!(cvt.buf = (Uint8*)ft_calloc(dlen * cvt.len_mult)),
		"Failed to alloc cvt.buf");
	ft_memcpy(cvt.buf, data, dlen);
	cvt.len = dlen;
	SDL_ConvertAudio(&cvt);
	SDL_FreeWAV(data);
	error_check(!(ret = (t_track*)ft_calloc(sizeof(t_track))), "E:Alloc track");
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

t_sound			*s_ini(char loop, char priority, char type, float vol)
{
	t_sound	*ret;

	if (!(ret = (t_sound*)malloc(sizeof(t_sound))))
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

float			sound_mag(t_vec3 v1, t_vec3 v2)
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

float			distance_vol(float vol_max, float dist, float mdist)
{
	float	max_dist;
	float	ret;

	max_dist = mdist != -1 ? mdist : SOUND_DIST;
	vol_max = vol_max > 1.0f ? 1.0f : vol_max;
	vol_max = vol_max < 0.0f ? 0 : vol_max;
	if (dist >= max_dist || (!max_dist && dist) || !vol_max)
		return (0.0f);
	else if (!max_dist && !dist)
		return (vol_max);
	ret = vol_max * (1 - dist / max_dist);
	ret = ret > 1 ? 1 : ret;
	return (ret);
}
