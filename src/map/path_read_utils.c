/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_read_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:32:06 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:46:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

int32_t			get_num_path_nodes(t_doom3d *app)
{
	int32_t		num_path_nodes;
	int32_t		i;

	num_path_nodes = 0;
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_path)
			num_path_nodes++;
	return (num_path_nodes);
}

int32_t			get_num_npcs(t_doom3d *app)
{
	int32_t		num_npcs;
	int32_t		i;

	num_npcs = 0;
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_npc)
			num_npcs++;
	return (num_npcs);
}

static int32_t	read_patrol_path(t_doom3d *app, char *contents, t_npc *npc,
					int32_t num_patrol_path_nodes)
{
	int32_t		j;
	int32_t		k;
	uint32_t	object_id;
	t_3d_object	*obj;
	int32_t		offset;

	j = -1;
	k = 0;
	offset = 0;
	while (++j < num_patrol_path_nodes)
	{
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		if (obj && npc)
			npc->patrol_path[k++] = obj;
	}
	return (offset);
}

int32_t			read_npc_path(t_doom3d *app, char *contents, int32_t offset)
{
	t_3d_object	*obj;
	t_npc		*npc;
	uint32_t	object_id;
	int32_t		num_patrol_path_nodes;

	npc = NULL;
	ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	obj = find_object_by_id(app, object_id);
	num_patrol_path_nodes = 0;
	if (obj)
	{
		npc = obj->params;
		ft_memcpy(&num_patrol_path_nodes, contents + offset,
			sizeof(int32_t));
		npc->num_patrol_path_nodes = npc->num_patrol_path_nodes;
	}
	offset += sizeof(int32_t);
	offset += read_patrol_path(app, contents, npc, num_patrol_path_nodes);
	return (offset);
}
