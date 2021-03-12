/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_mp_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:51:41 by phakakos          #+#    #+#             */
/*   Updated: 2021/03/12 15:51:44 by phakakos         ###   ########.fr       */
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
{	ft_printf("mp_close()\n");
	int		i;
	t_sound	*curr;
	t_sound	*next;

	ft_printf("audio locked\n");
	SDL_LockAudioDevice(app->mp.audev);
	SDL_PauseAudioDevice(app->mp.audev, 1);
	i = -1;
	ft_printf("freeing library\n");
	while (++i < SOUNDS + 1)
		free(app->mp.library[i]->data);
	curr = app->mp.tracks;
	ft_printf("freeing music\n");
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	ft_printf("freeing effects\n");
	curr = app->mp.effects;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	ft_printf("closing audio\n");
	SDL_CloseAudioDevice(app->mp.audev);
	ft_printf("audio closed\n");
}
