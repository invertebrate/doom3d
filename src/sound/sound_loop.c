/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:31:31 by phakakos          #+#    #+#             */
/*   Updated: 2021/06/21 15:35:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Helper for the audio loop. Moves all active sounds by len.
** Pops fully played sounds and resets looping sounds
*/

static void	mp_move(t_sound **start, int len, t_sound *curr,
				t_sound *prev[2])
{
	while (curr)
	{
		if (curr->state == SPLAYING)
			curr->pos += len;
		if (curr->pos >= curr->sound->len)
		{
			if (curr->loop)
				curr->pos = 0;
			else
			{
				if (prev[0])
					prev[0]->next = curr->next;
				else
					*start = curr->next;
				prev[1] = curr;
				curr = curr->next;
				free(prev[1]);
			}
		}
		else
		{
			prev[0] = curr;
			curr = curr->next;
		}
	}
}

/*
** Music player mix loop helper, find the next sound to play
** Returns in order the next active track or NULL if none
*/

static t_sound	*mp_mix_next(t_sound *start)
{
	t_sound	*curr;
	t_sound	*ret;

	curr = start;
	ret = NULL;
	while (!ret && curr)
	{
		if (curr->state == SPLAYING && curr->vol > 0)
			ret = curr;
		curr = curr->next;
	}
	return (ret);
}

/*
** Find playable sounds
*/

static t_sound	*mp_mixing(t_sound *curr, t_mp *mp)
{
	Uint32	amount;

	curr = mp_mix_next(curr);
	if (!curr)
		return (curr);
	amount = curr->sound->len - curr->pos;
	if (amount > (Uint32)mp->len)
		amount = (Uint32)mp->len;
	SDL_MixAudioFormat(mp->stream, &curr->sound->data[curr->pos],
		mp->auspec.format, amount, SDL_MIX_MAXVOLUME * curr->vol);
	return (curr);
}

/*
** Loop thru sounds till max has been reached or no more sounds to play
*/

static void	playing_audio(t_mp *mp, t_sound **start, int max)
{
	t_sound	*curr;
	t_sound	*prev[2];
	int		played;

	curr = *start;
	if (!curr)
		return ;
	played = 0;
	while (played < max && curr)
	{
		curr = mp_mixing(curr, mp);
		if (!curr)
			break ;
		played++;
		curr = curr->next;
	}
	prev[0] = NULL;
	prev[1] = NULL;
	mp_move(start, mp->len, *start, prev);
}

/*
** Music player main loop
*/

void	mp_au_mix(void *para, Uint8 *stream, int len)
{
	t_mp	*mp;

	mp = (t_mp *)para;
	SDL_memset(stream, 0, len);
	mp->stream = stream;
	mp->len = len;
	playing_audio(mp, &mp->tracks, NUM_MUSIC);
	playing_audio(mp, &mp->effects, NUM_SEFFECTS);
	mp->stream = NULL;
	mp->len = 0;
}
