/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:11:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:20:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** 1. Count path node objects that have been read
** 2. Read object id bytes
** 3. Find object and set path node to be its params
** 4. Set neighbors for that path node by reading neighbor id and finding its
** corresponding object
*/

int32_t		read_path_nodes(t_doom3d *app, char *contents)
{
	int32_t		offset;
	uint32_t	object_id;
	t_3d_object	*obj;
	t_path_node	*path_node;
	int32_t		num_path_nodes;
	int32_t		i;
	int32_t		j;

	offset = 0;
	num_path_nodes = 0;
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_path)
			num_path_nodes++;
	i = -1;
	while (++i < num_path_nodes)
	{
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		path_node = obj->params;
		ft_memcpy(&path_node->num_neighbors, contents + offset, sizeof(int32_t));
		offset += sizeof(int32_t);
		j = -1;
		while (++j < path_node->num_neighbors)
		{
			ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			obj = find_object_by_id(app, object_id);
			path_node->neighbors[j] = obj;
		}
	}
	return (offset);
}

/*
** Reads npc patrol path information, but if npc was deleted, its information
** is not set even if the patrol path information is found in map data
*/

int32_t		read_path_node_npc_links(t_doom3d *app, char *contents)
{
	int32_t		offset;
	uint32_t	object_id;
	t_3d_object	*obj;
	t_npc		*npc;
	int32_t		num_npcs;
	int32_t		num_patrol_path_nodes;
	int32_t		i;
	int32_t		j;
	int32_t		k;

	offset = 0;
	num_npcs = 0;
	npc = NULL;
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_npc)
			num_npcs++;
	i = -1;
	while (++i < num_npcs)
	{
		num_patrol_path_nodes = 0;
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		if (obj) {
			npc = obj->params;
			ft_memcpy(&num_patrol_path_nodes, contents + offset, sizeof(int32_t));
			npc->num_patrol_path_nodes = num_patrol_path_nodes;
		}
		offset += sizeof(int32_t);
		j = -1;
		k = 0;
		while (++j < num_patrol_path_nodes)
		{
			ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			obj = find_object_by_id(app, object_id);
			if (obj && npc)
				npc->patrol_path[k++] = obj;
		}
	}
	return (offset);
}
