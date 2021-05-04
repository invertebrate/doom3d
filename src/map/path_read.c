/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:11:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 18:35:37 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static int32_t	set_path_node_neighbor(t_doom3d *app,
						char *contents, int32_t offset, t_path_node *path_node)
{
	t_3d_object	*obj;
	uint32_t	object_id;
	int32_t		i;

	i = -1;
	while (++i < path_node->num_neighbors)
	{
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		path_node->neighbors[i] = obj;
	}
	return (offset);
}

/*
** 1. Count path node objects that have been read
** 2. Read object id bytes
** 3. Find object and set path node to be its params
** 4. Set neighbors for that path node by reading neighbor id and finding its
** corresponding object
*/

int32_t	read_path_nodes(t_doom3d *app, char *contents)
{
	int32_t		offset;
	uint32_t	object_id;
	t_3d_object	*obj;
	int32_t		num_path_nodes;
	int32_t		i;

	offset = 0;
	num_path_nodes = get_num_path_nodes(app);
	i = -1;
	while (++i < num_path_nodes)
	{
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		ft_memcpy(&((t_path_node *)obj->params)->num_neighbors,
			contents + offset, sizeof(int32_t));
		offset += sizeof(int32_t);
		offset = set_path_node_neighbor(app, contents, offset, obj->params);
	}
	return (offset);
}

/*
** Reads npc patrol path information, but if npc was deleted, its information
** is not set even if the patrol path information is found in map data
*/

int32_t	read_path_node_npc_links(t_doom3d *app, char *contents)
{
	int32_t		offset;
	int32_t		num_npcs;
	int32_t		i;

	offset = 0;
	num_npcs = get_num_npcs(app);
	i = -1;
	while (++i < num_npcs)
		offset = read_npc_path(app, contents, offset);
	return (offset);
}
