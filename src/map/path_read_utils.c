/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_read_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:32:06 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 18:31:58 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

int32_t	get_num_path_nodes(t_doom3d *app)
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

int32_t	get_num_npcs(t_doom3d *app)
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

static void	read_patrol_path_nodes(t_doom3d *app, char *contents,
								int32_t *offset, t_patrol_path_vars vars)
{
	int32_t	j;
	int32_t	k;

	j = -1;
	k = 0;
	while (++j < vars.num_patrol_path_nodes)
	{
		ft_memcpy(&vars.object_id, contents + *offset, sizeof(uint32_t));
		*offset += sizeof(uint32_t);
		vars.obj = find_object_by_id(app, vars.object_id);
		if (vars.obj && vars.npc)
			vars.npc->patrol_path[k++] = vars.obj;
	}
}

int32_t	read_npc_path(t_doom3d *app, char *contents, int32_t offset)
{
	t_patrol_path_vars	vars;

	vars.npc = NULL;
	ft_memcpy(&vars.object_id, contents + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	vars.obj = find_object_by_id(app, vars.object_id);
	vars.num_patrol_path_nodes = 0;
	if (vars.obj)
	{
		vars.npc = vars.obj->params;
		ft_memcpy(&vars.num_patrol_path_nodes, contents + offset,
			sizeof(int32_t));
		vars.npc->num_patrol_path_nodes = vars.num_patrol_path_nodes;
	}
	offset += sizeof(int32_t);
	read_patrol_path_nodes(app, contents, &offset, vars);
	return (offset);
}
