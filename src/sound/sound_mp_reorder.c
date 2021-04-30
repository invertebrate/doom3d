/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_mp_reorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 12:21:21 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/26 12:21:22 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		mp_del_dupe(t_sound **new, t_sound *curr)
{
	if ((*new)->type == curr->type &&
		(*new)->sound == curr->sound &&
		(*new)->vol == curr->vol &&
		(*new)->loop == curr->loop &&
		(*new)->pos == curr->pos &&
		(*new)->priority == curr->priority &&
		(*new)->state == curr->state)
	{
		free(*new);
		*new = NULL;
	}
}

static void		mp_reorder_insert(t_sound **new, t_sound **cur, t_sound **prev)
{
	(*prev)->next = *new;
	(*new)->next = *cur;
	*cur = *new;
	*new = NULL;
}

/*
** Order track list by priority, and add a new to the chain.
** Previous ones with same prio hold the priority
** prev should always be NULL
*/

void			mp_reorder(t_sound **start, t_sound *new, t_sound *prev)
{
	t_sound	*curr;

	if (!(curr = *start))
	{
		*start = new;
		return ;
	}
	while (curr->next)
	{
		if (new)
			mp_del_dupe(&new, curr);
		if (new && new->priority > curr->priority)
			mp_reorder_insert(&new, &curr, &prev);
		if (curr->priority < curr->next->priority)
		{
			prev->next = curr->next;
			curr->next = curr->next->next;
			curr->next->next = curr;
			curr = prev;
		}
		prev = curr;
		curr = curr->next;
	}
	curr->next = new;
}
