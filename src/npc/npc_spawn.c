/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_spawn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:35:21 by ahakanen          #+#    #+#             */
/*   Updated: 2020/12/22 19:52:25 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	parse_type(t_npc *npc, int type)
{
	if (type = 0)
		SETVALUESTYPE(npc);
	if (type = 1)
		SETVALUESTYPE(npc);
}

/* spawn on position facing direction with given model */

void	npc_spawn(t_list *npc_list, t_vec3 pos, t_vec2 dir, int type, int hp_override)
{
	static int	next_id;
	t_npc		*npc;
	t_list		tmp;

	ml_vector3_copy(pos, npc->pos);
	npc->forward[0] = dir[0];
	npc->forward[1] = 0;
	npc->forward[2] = 0;
	npc->sideways[0] = 0;
	npc->sideways[1] = dir[1];
	npc->sideways[2] = 0;
	parse_type(&npc, type);
	if (hp_override != 0)
		npc->hp = hp_override;
	npc->id = next_id;
	next_id++;
	tmp.content = npc;
	tmp.content_size = sizeof(t_npc);
	ft_lstadd(npc_list, npc);
}
