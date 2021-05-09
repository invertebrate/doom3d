/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_move_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 17:39:49 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/03 17:40:47 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	reset_patrol_path_if_needed(t_npc *npc)
{
	if (npc->patrol_path[npc->patrol_path_index] == NULL)
		npc->patrol_path_index = 0;
}

void	handle_reaching_waypoint(t_doom3d *app, t_npc *npc, t_vec3 diff)
{
	if (ml_vector3_mag(diff) < app->unit_size * 1.5)
	{
		npc->patrol_path_index++;
		if (npc->type == npc_type_elevator)
			npc->speed = 0;
	}
}

void	init_pathfind_vars(t_pathfind_vars *vars)
{
	vars->start_id = 0;
	vars->end_id = 0;
	vars->closest = INFINITY;
	vars->i = -1;
}

void	find_start_id(t_doom3d *app, t_pathfind_vars *vars, t_vec3 start)
{
	while (++vars->i < MAX_PATH_NODE_NETWORK_SIZE
		&& app->path_node_network[vars->i])
	{
		ml_vector3_sub(start,
			app->path_node_network[vars->i]->parent_obj->position, vars->tmp);
		if (ml_vector3_mag(vars->tmp) < vars->closest)
		{
			vars->closest = ml_vector3_mag(vars->tmp);
			vars->start_id = app->path_node_network[vars->i]->parent_obj->id;
		}
	}
}
