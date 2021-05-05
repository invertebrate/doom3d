/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_astar_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 18:53:14 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/03 17:44:48 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	init_astar_vars(t_astar_vars *vars)
{
	vars->i = -1;
	vars->start = NULL;
	vars->end = NULL;
}

void	init_astar_vars2(t_astar_vars *v)
{
	v->current = v->start;
	v->start->local_goal = 0;
	v->start->global_goal = dist_between_nodes(v->start, v->end);
	v->arr_pos = 0;
	ft_memset(&v->not_tested_nodes, 0, sizeof(t_path_node *)
		* MAX_PATH_NODE_NETWORK_SIZE);
	v->not_tested_nodes[v->arr_pos++] = v->start;
}

void	init_astar_vars3(t_astar_vars *v)
{
	v->current = v->not_tested_nodes[v->i];
	v->current->is_visited = true;
	v->i = -1;
}

float	dist_between_nodes(t_path_node *start, t_path_node *end)
{
	t_vec3	tmp;

	ml_vector3_sub(start->parent_obj->position, end->parent_obj->position, tmp);
	return (ml_vector3_mag(tmp));
}

void	init_astar_node(t_doom3d *app, t_astar_vars *v,
										uint32_t start_id, uint32_t end_id)
{
	if (app->path_node_network[v->i]->parent_obj->id == start_id)
		v->end = app->path_node_network[v->i];
	if (app->path_node_network[v->i]->parent_obj->id == end_id)
		v->start = app->path_node_network[v->i];
	app->path_node_network[v->i]->global_goal = INFINITY;
	app->path_node_network[v->i]->local_goal = INFINITY;
	app->path_node_network[v->i]->is_visited = false;
	app->path_node_network[v->i]->parent = NULL;
}
