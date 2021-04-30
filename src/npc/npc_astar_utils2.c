/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_astar_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 19:45:59 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/30 20:14:38 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	astar_handle_node(t_astar_vars *v)
{
	t_path_node	*tmp;

	tmp = v->current->neighbors[v->i]->params;
	if (((t_path_node *)v->current->neighbors[v->i]->params)->is_visited ==
																		false)
		v->not_tested_nodes[v->arr_pos++] = v->current->neighbors[v->i]->params;
	v->possibly_lower_goal = v->current->local_goal +
		dist_between_nodes(v->current,
		(t_path_node *)v->current->neighbors[v->i]->params);
	if (v->possibly_lower_goal <
		((t_path_node *)v->current->neighbors[v->i]->params)->local_goal)
	{
		((t_path_node *)v->current->neighbors[v->i]->params)->parent =
													v->current->parent_obj;
		((t_path_node *)v->current->neighbors[v->i]->params)->local_goal =
													v->possibly_lower_goal;
		((t_path_node *)v->current->neighbors[v->i]->params)->global_goal =
			v->possibly_lower_goal + dist_between_nodes(tmp, v->end);
	}
}

void	init_astar_vars4(t_doom3d *app, t_astar_vars *v)
{
	v->obj = find_object_by_id(app, v->end->parent_obj->id);
	v->current = v->obj->params;
	v->i = 0;
}
