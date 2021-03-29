/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_trigger_onhit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:35:16 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/29 16:19:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_trigger_onhit(t_doom3d *app, t_3d_object *obj, int damage)
{
	t_npc	*npc;

	npc = obj->params;
	npc->hp -= damage;
	if (npc->type != npc_type_elevator)
		npc->state = state_attack;
	npc->interest = npc->max_interest;
	if (npc->hp <= 0)
	{
		npc->state = state_death_anim;
		// ft_printf("npc killed!\n"); //test
		doom3d_push_event(app, event_object_delete,
			obj, NULL);
	}
	// ft_printf("npc hit for %d damage! current hp: %d\n",
		// damage, npc->hp); //test
}