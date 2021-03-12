/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:19:27 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/12 03:30:21 by ahakanen         ###   ########.fr       */
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
	ft_memset(app->path_node_network, 0, sizeof(t_path_node *) * MAX_PATH_NODE_NETWORK_SIZE + 1);
	while (++i < (int32_t)(app->active_scene->num_objects +
					app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		if (obj->type == object_type_path)
		{
			node = obj->params;
			if (node->num_neighbors > 0 && 
				app->path_node_network_count < MAX_PATH_NODE_NETWORK_SIZE)
			{
				app->path_node_network[app->path_node_network_count++] = node;
			}
		}
	}
}

static float	dist_between_nodes(t_path_node *start, t_path_node *end)
{
	t_vec3	tmp;

	ml_vector3_sub(start->parent_obj->position, end->parent_obj->position, tmp);
	return (ml_vector3_mag(tmp));
}

static void		sort_array(t_path_node **array)
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
			if (array[j] && array[j + 1] && array[j]->global_goal > array[j + 1]->global_goal)
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
/*
static void		delete_node(void *node, size_t size)
{
	(void)size;
	if (node != NULL)
		free(node);
}*/

/*
**	Algorithm for pathfinding
*/

static void		solve_Astar(t_doom3d *app, t_npc *npc, uint32_t start_id, uint32_t end_id)
{
	t_path_node	*start;
	t_path_node	*end;
	t_path_node	*current;
	t_path_node	*not_tested_nodes[MAX_PATH_NODE_NETWORK_SIZE];
	t_3d_object	*obj;
	t_3d_object	*tmp_obj[MAX_PATH_NODE_NETWORK_SIZE];
	float		possibly_lower_goal;
	int			i;
	int			arr_pos;

	i = -1;
	start = NULL;
	end = NULL;
	while (++i < MAX_PATH_NODE_NETWORK_SIZE && app->path_node_network[i])
	{
		if (app->path_node_network[i]->parent_obj->id == start_id)
			end = app->path_node_network[i];
		if (app->path_node_network[i]->parent_obj->id == end_id)
			start = app->path_node_network[i];
		app->path_node_network[i]->global_goal = INFINITY;
		app->path_node_network[i]->local_goal = INFINITY;
		app->path_node_network[i]->is_visited = false;
		app->path_node_network[i]->parent = NULL;
	}
	if (!start || !end)
		return ;
	current = start;
	start->local_goal = 0;
	start->global_goal = dist_between_nodes(start, end);
	arr_pos = 0;
	ft_memset(&not_tested_nodes, 0, sizeof(t_path_node *) * MAX_PATH_NODE_NETWORK_SIZE);
	not_tested_nodes[arr_pos++] = start;
	while (current->parent_obj->id != end->parent_obj->id)
	{
		sort_array(not_tested_nodes);
		i = 0;
		while (i < MAX_PATH_NODE_NETWORK_SIZE && not_tested_nodes[i]->is_visited)
			i++;
		if (!not_tested_nodes[i])
			break ;
		current = not_tested_nodes[i];
		current->is_visited = true;
		i = -1;
		while (++i < current->num_neighbors)
		{
			if (((t_path_node *)current->neighbors[i]->params)->is_visited == false)
			{
				not_tested_nodes[arr_pos++] = current->neighbors[i]->params;
			}
			possibly_lower_goal = current->local_goal + dist_between_nodes(current, (t_path_node *)current->neighbors[i]->params);
			if (possibly_lower_goal < ((t_path_node *)current->neighbors[i]->params)->local_goal)
			{
				((t_path_node *)current->neighbors[i]->params)->parent = current->parent_obj;
				((t_path_node *)current->neighbors[i]->params)->local_goal = possibly_lower_goal;
				((t_path_node *)current->neighbors[i]->params)->global_goal = possibly_lower_goal + dist_between_nodes((t_path_node *)current->neighbors[i]->params, end);
			}
		}
	}
	obj = find_object_by_id(app, end->parent_obj->id);
	current = obj->params;
	i = 0;
	while (current && i < MAX_PATH_NODE_NETWORK_SIZE)
	{
		tmp_obj[i++] = find_object_by_id(app, current->parent_obj->id);
		if (current->parent)
			current = current->parent->params;
		else
			current = NULL;
	}
	while (--i >= 0)
		npc->attack_path[i] = tmp_obj[i];
	npc->attack_path_index = 0;
}

void			npc_find_path(t_doom3d *app, t_npc *npc, t_vec3	start, t_vec3 end)
{
	int			i;
	int			start_id;
	int			end_id;
	float		closest;
	t_vec3		tmp;

	start_id = 0;
	end_id = 0;
	closest = INFINITY;
	i = -1;
	path_node_network_init(app);
	while (++i < MAX_PATH_NODE_NETWORK_SIZE && app->path_node_network[i])
	{
		ml_vector3_sub(start, app->path_node_network[i]->parent_obj->position, tmp);
		if (ml_vector3_mag(tmp) < closest)
		{
			closest = ml_vector3_mag(tmp);
			start_id = app->path_node_network[i]->parent_obj->id;
		}
	}
	closest = INFINITY;
	i = -1;
	while (++i < MAX_PATH_NODE_NETWORK_SIZE && app->path_node_network[i])
	{
		ml_vector3_sub(end, app->path_node_network[i]->parent_obj->position, tmp);
		if (ml_vector3_mag(tmp) < closest)
		{
			closest = ml_vector3_mag(tmp);
			end_id = app->path_node_network[i]->parent_obj->id;
		}
	}
	if (start_id && end_id)
		solve_Astar(app, npc, start_id, end_id);
}