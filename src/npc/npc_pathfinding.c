/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:19:27 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/10 23:46:48 by ahakanen         ###   ########.fr       */
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
	ft_memset(app->path_node_network, 0, sizeof(t_path_node *) * MAX_PATH_NODE_NETWORK_SIZE);
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

static void		lst_swap(t_list	*node1, t_list *node2)
{
	t_list	*tmp;

	tmp = node1->content;
	node1->content = node2->content;
	node2->content = tmp;
}

static void		list_sort(t_list *list)
{
	t_bool		swapped;
	t_list		*tmp;
	t_path_node	*node_a;
	t_path_node	*node_b;


	swapped = true;
	while (swapped)
	{
		swapped = false;
		tmp = list;
		while (tmp)
		{
			node_a = tmp->content;
			if (tmp->next)
				node_b = tmp->next->content;
			else
				break ;
			if (node_a && node_a->global_goal > node_b->global_goal)
			{
				lst_swap(node_a, node_b);
				swapped = true;
				break ;
			}
			else
				tmp = tmp->next;
		}
	}
}

static void		delete_node(void *node, size_t size)
{
	(void)size;
	if (node != NULL)
		free(node);
}

/*
**	Algorithm for pathfinding
*/

static void		solve_Astar(t_doom3d *app, t_npc *npc, int start_id, int end_id)
{
	t_path_node	tmp_network[MAX_PATH_NODE_NETWORK_SIZE];
	t_path_node	*start;
	t_path_node	*end;
	t_path_node	*current;
	t_list		*not_tested_nodes;
	t_list		*tmp;
	float		possibly_lower_goal;
	int			i;

	i = -1;

	ft_memset(&tmp_network, 0, sizeof(t_path_node) * MAX_PATH_NODE_NETWORK_SIZE);
	while (++i < MAX_PATH_NODE_NETWORK_SIZE && app->path_node_network[i])
	{
		ft_memcpy(&tmp_network[i], app->path_node_network[i], sizeof(t_path_node));
		if (tmp_network[i].parent_obj->id == start_id)
			end = &tmp_network[i];
		if (tmp_network[i].parent_obj->id == end_id)
			start = &tmp_network[i];
		tmp_network[i].global_goal = INFINITY;
		tmp_network[i].local_goal = INFINITY;
	}
	current = start;
	start->local_goal = 0;
	start->global_goal = dist_between_nodes(start, end);
	not_tested_nodes = ft_lstnew(start, sizeof(t_path_node *));
	while (not_tested_nodes && current != end)
	{
		list_sort(not_tested_nodes);
		while (not_tested_nodes && ((t_path_node *)not_tested_nodes->content)->is_visited)
		{
			tmp = not_tested_nodes->next;
			free(not_tested_nodes->content);
			free(not_tested_nodes);
			not_tested_nodes = tmp;
		}
		if (!not_tested_nodes)
			break ;
		current = not_tested_nodes->content;
		current->is_visited = true;
		i = -1;
		while (++i < current->num_neighbors)
		{
			if (((t_path_node *)current->neighbors[i]->params)->is_visited == false)
				ft_lstappend(not_tested_nodes, ft_lstnew(current, sizeof(t_path_node *)));
			possibly_lower_goal = current->local_goal + dist_between_nodes(current, (t_path_node *)current->neighbors[i]->params);
			if (possibly_lower_goal < ((t_path_node *)current->neighbors[i]->params)->local_goal)
			{
				((t_path_node *)current->neighbors[i]->params)->parent = current;
				((t_path_node *)current->neighbors[i]->params)->local_goal = possibly_lower_goal;
				((t_path_node *)current->neighbors[i]->params)->global_goal = possibly_lower_goal + dist_between_nodes((t_path_node *)current->neighbors[i]->params, end);
			}
		}
	}
	ft_lstdel(not_tested_nodes, delete_node);
	current = start;
	i = 0;
	while (current && i < MAX_PATH_NODE_NETWORK_SIZE)
	{
		npc->attack_path[i++] = current->parent_obj;
		current = current->parent;
	}
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
	i = -1;
	while (++i < MAX_PATH_NODE_NETWORK_SIZE && app->path_node_network[i])
	{
		ml_vector3_sub(start, app->path_node_network[i]->parent_obj->position, tmp);
		if (ml_vector3_mag(tmp) < closest)
		{
			closest = ml_vector3_mag(tmp);
			start_id = app->path_node_network[i]->parent_obj->id;
		}
	}
	i = -1;
	while (++i < MAX_PATH_NODE_NETWORK_SIZE && app->path_node_network[i])
	{
		ml_vector3_sub(end, app->path_node_network[i]->parent_obj->position, tmp);
		if (ml_vector3_mag(tmp) < closest)
		{
			closest = ml_vector3_mag(tmp);
			start_id = app->path_node_network[i]->parent_obj->id;
		}
	}
	if (start_id && end_id)
		solve_Astar(app, npc, start_id, end_id);
}