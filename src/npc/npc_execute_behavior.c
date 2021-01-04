/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_execute_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:22:03 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/04 13:45:52 by ahakanen         ###   ########.fr       */
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
		l3d_3d_object_translate(tmp->obj, -tmp->dir[0], -tmp->dir[1], -tmp->dir[2]);
		tmp->pos[0] -= tmp->dir[0];
		tmp->pos[1] -= tmp->dir[1];
		tmp->pos[2] -= tmp->dir[2];
	}
}