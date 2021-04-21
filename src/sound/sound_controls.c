/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:22:55 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/18 20:15:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Delete all the given type sounds from the queue
*/
static void	sound_del(t_sound **start, char type)
{
	t_sound	*curr;
	t_sound	*prev[2];

	curr = *start;
	prev[0] = NULL;
	while (curr)
	{
		if (!type || curr->type == type ||
			(type < 0 && curr->type != ft_abs(type)))
		{
			if (prev[0])
				prev[0]->next = curr->next;
			else
				*start = curr->next;
			prev[1] = curr;
			curr = curr->next;
			free(prev[1]);
		}
		else
		{
			prev[0] = curr;
			curr = curr->next;
		}
	}
}

/*
** Edit all the matching type sounds to have the set state
*/
static void	sound_edit(t_sound *start, char type, char state)
{
	t_sound	*curr;

	curr = start;
	while (curr)
	{
		if (!type || curr->type == type ||
			(type < 0 && curr->type != ft_abs(type)))
			curr->state = state;
		curr = curr->next;
	}
}

/*
** MUSIC PLAYER TYPE CONTROLLER
** change sounds based on type
** type == t_sound_type; Negative to do inverse search; 0 == all
** sound = app->mp.tracks == 1 app->mp.effects == 2 both == 0;
** state = new state; SPLAYING, SPAUSED, SSTOPPED == remove
*/
void		mp_typec(t_doom3d *app, char type, char sound, char state)
{
	SDL_LockAudioDevice(app->mp.audev);
	if (!sound || sound == 1)
	{
		if (state != 3)
			sound_edit(app->mp.tracks, type, state);
		else if (state == 3)
			sound_del(&app->mp.tracks, type);
	}
	if (!sound || sound == 2)
	{
		if (state != 3)
			sound_edit(app->mp.effects, type, state);
		else if (state == 3)
			sound_del(&app->mp.effects, type);
	}
	SDL_UnlockAudioDevice(app->mp.audev);
}
