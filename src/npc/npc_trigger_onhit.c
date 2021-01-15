/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_trigger_onhit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:35:16 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 22:34:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_trigger_onhit(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*npc;

	npc = obj->params;
	npc->hp -= app->player.equipped_weapon->damage_per_hit;
	if (npc->hp <= 0)
	{
		npc->state = state_death_anim;
		ft_printf("npc killed!\n"); //test
		object_set_for_deletion(app, obj); //test
	}
	ft_printf("npc hit for %d damage! current hp: %d\n", app->player.equipped_weapon->damage_per_hit, npc->hp); //test
}