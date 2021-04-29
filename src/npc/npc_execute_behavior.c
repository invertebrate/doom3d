/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_execute_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:22:03 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/29 18:49:12 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

//npc enemy actions determine npc state
// this calls actions based on surroundings and states
//npc update calls execute behaviour after or before it has updated the npc

void	npc_execute_behavior(t_doom3d *app, t_3d_object *npc_obj)
{
	t_npc	*npc;

	if (npc_obj == NULL || npc_obj->params == NULL)
		return ;
	npc = (t_npc*)(npc_obj->params);

	//1. check if attacking and continue attacking until over

	//2. check aggro
	//3. check if should move and move
	if (npc->state == state_attack)// checks if npc attacking and lets it finish the attack
		return ;
	npc_check_aggro(app, npc);//this checks line of sight and range to player and changes state to attack if should
	if (npc->state == state_idle || npc->state == state_moving)
		npc_handle_movement(app, npc);


	if (npc->state == state_idle)
	{
		npc_move_step_to_waypoint(npc_obj);
	}
	else if (npc->state == state_attack)
	{
		if (npc_has_line_of_sight(app, npc_obj) == false)
			npc_move_step_to_waypoint(npc_obj);
		else if (npc->advance == true)
		{
			l3d_3d_object_translate(npc_obj,
				npc->dir[0], 0, npc->dir[2]);
			l3d_object_aabb_update(npc_obj);
		}
	}
}