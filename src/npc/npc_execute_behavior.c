/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_execute_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:22:03 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/05 19:43:02 by ohakola          ###   ########.fr       */
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
		ml_vector3_copy(tmp->obj->position, tmp->pos);
	}
}