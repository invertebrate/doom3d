/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patrol_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:48:18 by ahakanen          #+#    #+#             */
/*   Updated: 2021/02/01 16:47:40 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	patrol_path_link_node(t_3d_object *node_obj, t_3d_object *obj, int slot)
{
	t_npc		*npc;
	t_path_node	*node;

	npc = obj->params;
	node = node_obj->params;
	if (slot < MAX_PATROL_NODES)
	{
		ml_vector3_copy(node->parent->position, npc->patrol_path[slot]);
		ft_printf("path node id %d added to npc id %d patrol path slot %d\n", node_obj->id, obj->id, slot);//test
	}
	else
		ft_printf("invalid patrol path node slot! \n");
}
