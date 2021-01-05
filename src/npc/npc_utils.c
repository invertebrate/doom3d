/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:38:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/05 15:42:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Useful in collisions or editor selection :). When you have access to an
** object, and need its npc (if it has one)
*/

t_npc		*find_npc_by_object_id(t_doom3d *app, uint32_t object_id)
{
	t_list	*node;
	t_npc	*npc;

	node = app->active_scene->npc_list;
	while (node)
	{
		npc = (t_npc*)node->content;
		if (npc->obj->id == object_id)
			return (npc);
		node = node->next;
	}
	return (NULL);
}