/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_execute_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:22:03 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/02 16:28:41 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_execute_behavior(t_list *npc)
{
	t_npc	*tmp;

	tmp = npc->content;
	/*
	check state of npc
	*/
	if (tmp->state == state_idle)
	{
		/*
		DO IDLE THINGS WITH THIS NPC
		*/
	}
	else if (tmp->state == state_attack)
	{
		/*
		DO ATTACK THINGS WITH THIS NPC
		follow path to attack
		*/
		l3d_3d_object_translate(tmp->obj, -tmp->dir[0], 0, -tmp->dir[2]);
	}
}