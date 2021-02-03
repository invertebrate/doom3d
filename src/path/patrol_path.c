/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patrol_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:48:18 by ahakanen          #+#    #+#             */
/*   Updated: 2021/02/02 21:25:16 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	patrol_path_highlight(t_render_work *work)
{
	t_npc	*npc;
	int		i;

	if (work->app->active_scene->scene_id != scene_id_editor3d)
		return ;
	npc = work->app->editor.selected_object->params;
	i = 0;
	while (npc->patrol_path[i])
	{
		draw_aabb(work->app,
			work->framebuffer->sub_buffers[work->sub_buffer_i],
			&npc->patrol_path[i]->aabb, 0xff0000ff);
		i++;
	}
}

void	patrol_path_link_node(t_3d_object *node_obj, t_3d_object *obj, int slot)
{
	t_npc		*npc;
	t_path_node	*node;

	npc = obj->params;
	node = node_obj->params;
	if (slot < MAX_PATROL_NODES)
	{
		if (!npc->patrol_path[slot])
		{
			npc->num_patrol_path_nodes++;
			ft_printf("num_patrol_path_nodes = %d\n", npc->num_patrol_path_nodes);//test
		}
		if (npc->patrol_path[slot] == node->parent)
		{
			npc->patrol_path[slot] = NULL;
			npc->num_patrol_path_nodes--;
			ft_printf("num_patrol_path_nodes = %d\n", npc->num_patrol_path_nodes);//test
			ft_printf("path node id %d removed from npc id %d patrol path slot %d\n", node_obj->id, obj->id, slot);//test
		}
		else
		{
			npc->patrol_path[slot] = node->parent;
			ft_printf("path node id %d added to npc id %d patrol path slot %d\n", node_obj->id, obj->id, slot);//test
		}
	}
	else
		ft_printf("invalid patrol path node slot! \n");
}
