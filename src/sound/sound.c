/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:51:05 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/01 18:07:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** DEBUG ONLY
** --------- REMOVE BELOW BEFORE SUBMISSION ---------
*/

void	sound_len(t_sound *start)
{
	int		i;
	t_sound	*curr;

	i = 0;
	curr = start;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	ft_printf("sound lenght %d\n", i);
}

void	track_print(t_track *track)
{	ft_printf("mp_track_print()\n");
	if (!track)
	{
		printf("track: %p\n", track);
		return ;
	}
	ft_printf("track: %p\nlen %d\n", track->data, track->len);
}

void	sound_print(t_sound *sound)
{	ft_printf("mp_sound_print()\n");
	if (!sound)
	{
		printf("sound: %p\n", sound);
		return ;
	}
	track_print(sound->sound);
	ft_printf("sound: %d\nstate %d\ntype %d\nloop %d\nprio %d\nvolume %f\nnext %p\n",
	sound->pos, sound->state, sound->type, sound->loop, sound->priority, sound->vol, sound->next);
}

void	auspec_print(t_mp *mp)
{	ft_printf("mp_auspec_print()\n");
	ft_printf("format %d\nchannels %d\nsamples %d\ncallback %p\ndata %p\n",
	mp->auspec.format, mp->auspec.channels, mp->auspec.samples, mp->auspec.callback, mp->auspec.userdata);
}

void	mp_print(t_mp *mp)
{	ft_printf("mp_print()\n");
	int	i;

	ft_printf("mp %p\n", mp);
	auspec_print(mp);
	ft_printf("st %f sf %f\n", mp->st_vol, mp->sf_vol);
	i = -1;
	while (++i < SOUNDS)
	{
		printf("track add %p\n", mp->library[i]);
		track_print(mp->library[i]);
	}
	ft_printf("music\n");
	sound_print(mp->tracks);
	ft_printf("effects\n");
	sound_print(mp->effects);
}

/*
** DEBUG ONLY
** --------- REMOVE ABOVE BEFORE SUBMISSION ---------
*/


/*
** Reading WAV-files into t_track struct
*/

t_track		*read_sound(char *file, t_doom3d *app)
{
	t_track			*ret;
	SDL_AudioSpec	wave;
	Uint8			*data;
	Uint32			dlen;
	SDL_AudioCVT	cvt;

	if ( SDL_LoadWAV(file, &wave, &data, &dlen) == NULL ) {
		ft_dprintf(2, "Couldn't load %s: %s\n", file, SDL_GetError());
		return (NULL);
	}
	if (SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, 
		app->mp.auspec.format, app->mp.auspec.channels, app->mp.auspec.freq)
		== -1)
		return (NULL);
	if (!(cvt.buf = (Uint8*)malloc(dlen * cvt.len_mult)))
		return (NULL);
	ft_memcpy(cvt.buf, data, dlen);
	cvt.len = dlen;
	SDL_ConvertAudio(&cvt);
	SDL_FreeWAV(data);
	if (!(ret = (t_track*)malloc(sizeof(t_track))))
		return (NULL);
	ret->data = cvt.buf;
	ret->len = cvt.len_cvt;
	return (ret);
}



/*
** Order track list by priority, and add a new to the chain. Previous ones with same prio hold the priority
*/

void		mp_reorder(t_sound **start, t_sound *new)
{
	t_sound	*curr;
	t_sound	*prev;

	if (!(curr = *start))
	{
		*start = new;
		return ;
	}
	prev = NULL;
	while (curr->next)
	{
		if (new && new->priority > curr->priority)
		{
			prev->next = new;
			new->next = curr;
			prev = new;
			new = NULL;
		}
		else if (curr->priority < curr->next->priority)
		{
			prev->next = curr->next;
			curr->next = curr->next->next;
			curr->next->next = curr;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	curr->next = new;
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

	if(!(ret = (t_sound*)malloc(sizeof(t_sound))))
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
