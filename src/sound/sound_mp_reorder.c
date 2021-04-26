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
*/

void			mp_reorder(t_sound **start, t_sound *new)
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
