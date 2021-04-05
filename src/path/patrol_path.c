/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patrol_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:48:18 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/05 18:08:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	patrol_path_highlight(t_render_work *work)
{
	t_npc	*npc;
	int		i;

	if (work->app->active_scene->scene_id != scene_id_editor3d)
		return ;
	npc = work->app->editor.selected_objects[0]->params;
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
		}
		if (npc->patrol_path[slot] == node->parent_obj)
		{
			npc->patrol_path[slot] = NULL;
			npc->num_patrol_path_nodes--;
		}
		else
		{
			npc->patrol_path[slot] = node->parent_obj;
		}
		LOG_ERROR("Linked patrol path to slot %d object: %d", slot, obj->id);
	}
	else
		LOG_ERROR("Invalid patrol path node slot %d object: %d", slot, obj->id);
}
