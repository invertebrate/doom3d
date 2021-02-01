/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_execute_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:22:03 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/28 15:54:39 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_execute_behavior(t_doom3d *app, t_3d_object *npc_obj)
{
	t_npc	*npc;

	npc = npc_obj->params;
	(void)app;
	/*
	check state of npc
	*/
	if (npc->state == state_idle)
	{
		/*
		DO IDLE THINGS WITH THIS NPC, LIKE IDLE ANIMATION
		*/
		npc_move_step_to_waypoint(app, npc_obj);
	}
	else if (npc->state == state_attack)
	{
		/*
		DO ATTACK THINGS WITH THIS NPC
		follow path to attack
		// ToDo: Instead of translating towards direction, turn npc towards
		// player and then move to direction by delta_time * speed
		*/
		if (npc->advance == true)
			l3d_3d_object_translate(npc_obj,
				npc->dir[0], 0, npc->dir[2]);
	}
}