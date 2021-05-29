/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:19:27 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/29 17:58:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
**	Filters out path node objects that are not part of path node network
**	and makes an array with addresses to them
*/

void	path_node_network_init(t_doom3d *app)
{
	int			i;
	t_3d_object	*obj;
	t_path_node	*node;

	i = -1;
	app->path_node_network_count = 0;
	ft_memset(app->path_node_network, 0, sizeof(t_path_node *)
		* MAX_PATH_NODE_NETWORK_SIZE + 1);
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		if (obj->type == object_type_path)
		{
			node = obj->params;
			if (node->num_neighbors > 0
				&& app->path_node_network_count < MAX_PATH_NODE_NETWORK_SIZE)
			{
				app->path_node_network[app->path_node_network_count++] = node;
			}
		}
	}
}

static void	sort_array(t_path_node **array)
{
	int			i;
	int			j;
	t_path_node	*tmp;

	i = 0;
	while (i < MAX_PATH_NODE_NETWORK_SIZE)
	{
		j = 0;
		while (j < MAX_PATH_NODE_NETWORK_SIZE - 1)
		{
			if (array[j] && array[j + 1]
				&& array[j]->global_goal > array[j + 1]->global_goal)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
				j++;
			}
			else
				j++;
			i++;
		}
	}
}

static void	solve_astar2(t_doom3d *app, t_astar_vars *v, t_npc *npc)
{
	while (v->current && v->i < MAX_PATH_NODE_NETWORK_SIZE)
	{
		v->tmp_obj[v->i++] = find_object_by_id(app, v->current->parent_obj->id);
		if (v->current->parent)
			v->current = v->current->parent->params;
		else
			v->current = NULL;
	}
	while (--v->i >= 0)
		npc->attack_path[v->i] = v->tmp_obj[v->i];
	npc->attack_path_index = 0;
}

/*
**	Algorithm for pathfinding
*/

static void	solve_astar(t_doom3d *app, t_npc *npc,
							uint32_t start_id, uint32_t end_id)
{
	t_astar_vars	v;

	init_astar_vars(&v);
	while (++v.i < MAX_PATH_NODE_NETWORK_SIZE && app->path_node_network[v.i])
		init_astar_node(app, &v, start_id, end_id);
	if (!v.start || !v.end)
		return ;
	init_astar_vars2(&v);
	while (v.current->parent_obj->id != v.end->parent_obj->id)
	{
		sort_array(v.not_tested_nodes);
		v.i = 0;
		while (v.i < MAX_PATH_NODE_NETWORK_SIZE
			&& v.not_tested_nodes[v.i]->is_visited)
			v.i++;
		if (!v.not_tested_nodes[v.i])
			break ;
		init_astar_vars3(&v);
		while (++v.i < v.current->num_neighbors)
			astar_handle_node(&v);
	}
	init_astar_vars4(app, &v);
	solve_astar2(app, &v, npc);
}

void	npc_find_path(t_doom3d *app, t_npc *npc, t_vec3 start, t_vec3 end)
{
	t_pathfind_vars	vars;

	init_pathfind_vars(&vars);
	path_node_network_init(app);
	find_start_id(app, &vars, start);
	vars.closest = INFINITY;
	vars.i = -1;
	while (++vars.i < MAX_PATH_NODE_NETWORK_SIZE
		&& app->path_node_network[vars.i])
	{
		ml_vector3_sub(end,
			app->path_node_network[vars.i]->parent_obj->position, vars.tmp);
		if (ml_vector3_mag(vars.tmp) < vars.closest)
		{
			vars.closest = ml_vector3_mag(vars.tmp);
			vars.end_id = app->path_node_network[vars.i]->parent_obj->id;
		}
	}
	if (vars.start_id && vars.end_id)
		solve_astar(app, npc, vars.start_id, vars.end_id);
}
