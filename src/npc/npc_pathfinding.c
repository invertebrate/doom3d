/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:19:27 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/12 02:37:26 by ahakanen         ###   ########.fr       */
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

static void		swap(t_path_node *node_a, t_path_node *node_b)
{
	t_path_node	tmp;

	tmp = *node_a;
	*node_a = *node_b;
	*node_b = tmp;
}

static t_list	*list_sort(t_list *list)
{
	t_list		*start;
	t_list		*tmp;
	t_path_node	*node_a;
	t_path_node	*node_b;

	start = list;
	while (list)
	{
		tmp = list->next;
		while (tmp)
		{
			node_a = list->content;
			node_b = tmp->content;
			if (node_a->global_goal > node_b->global_goal)
				swap(node_a, node_b);
			tmp = tmp->next;
		}
		list = list->next;
	}
	return (start);
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
	t_list		*not_tested_nodes;
	t_list		*tmp;
	t_3d_object	*obj;
	t_3d_object	*tmp_obj[MAX_PATH_NODE_NETWORK_SIZE];
	float		possibly_lower_goal;
	int			i;

	i = -1;
	start = NULL;
	end = NULL;
	while (++i < MAX_PATH_NODE_NETWORK_SIZE && app->path_node_network[i])
	{
		if (app->path_node_network[i]->parent_obj->id == start_id)
			start = app->path_node_network[i];
		if (app->path_node_network[i]->parent_obj->id == end_id)
			end = app->path_node_network[i];
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
	not_tested_nodes = ft_lstnew(start, sizeof(t_path_node));
	while (not_tested_nodes && current->parent_obj->id != end->parent_obj->id)
	{
		not_tested_nodes = list_sort(not_tested_nodes);
		while (not_tested_nodes)
		{
			current = not_tested_nodes->content;
			obj = find_object_by_id(app, current->parent_obj->id);
			current = obj->params;
			if (((t_path_node *)obj)->is_visited == false)
				break ;
			tmp = not_tested_nodes->next;
			//free(not_tested_nodes->content);
			//free(not_tested_nodes);
			not_tested_nodes = tmp;
		}
		if (!not_tested_nodes)
			break ;
		current->is_visited = true;
		ft_printf("num neighbours = %d\n", ((t_path_node *)current->neighbors[i]->params)->num_neighbors);//test
		ft_printf("added to list!\n");//test
		i = -1;
		while (++i < current->num_neighbors)
		{
			if (((t_path_node *)current->neighbors[i]->params)->is_visited == false)
			{
				ft_lstadd(&not_tested_nodes, ft_lstnew(current->neighbors[i]->params, sizeof(t_path_node)));
			}
			possibly_lower_goal = current->local_goal + dist_between_nodes(current, (t_path_node *)current->neighbors[i]->params);
			if (possibly_lower_goal < ((t_path_node *)current->neighbors[i]->params)->local_goal)
			{
				((t_path_node *)current->neighbors[i]->params)->parent = obj;
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
		ft_printf("i = %d\n", i);//test
		tmp_obj[i++] = find_object_by_id(app, current->parent_obj->id);
		if (current->parent)
			current = current->parent->params;
		else
			current = NULL;
	}
	while (--i >= 0)
	{
		npc->attack_path[i] = tmp_obj[i];
		ft_printf("added path node id %d\n",npc->attack_path[i]->id);//test
	}
	//npc->attack_path[0] = find_object_by_id(app, start->parent_obj->id);
	npc->attack_path_index = 0;
	//ft_lstdel(&not_tested_nodes, delete_node);
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