/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 01:54:45 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:21:26 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		write_trigger_link(int32_t fd,
					t_trigger *trigger, int32_t j)
{
	int32_t		ret;

	if (trigger->linked_obj[j])
		ret = write(fd,
			&trigger->linked_obj[j]->id, sizeof(uint32_t));
	else
		ret = write(fd, 0, sizeof(uint32_t));
	(void)ret;
}

/*
** Writes trigger links
** of triggers that might have them
*/

void			write_trigger_link_information(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		j;
	int32_t		ret;
	t_trigger	*trigger;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type_trigger)
		{
			trigger = app->active_scene->objects[i]->params;
			ret = write(fd,
				&app->active_scene->objects[i]->id, sizeof(uint32_t));
			ret = write(fd, &trigger->num_links, sizeof(int32_t));
			j = -1;
			while (++j < trigger->num_links)
				write_trigger_link(fd, trigger, j);
		}
	}
	(void)ret;
}

/*
** For each object_type_path, writes the id of the object, num of neighbors
** and each neighbor id for the purpose of saving the connections
*/

void			write_path_object_information(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		j;
	int32_t		ret;
	t_path_node	*path_node;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type_path)
		{
			path_node = app->active_scene->objects[i]->params;
			ret = write(fd,
				&app->active_scene->objects[i]->id, sizeof(uint32_t));
			ret = write(fd, &path_node->num_neighbors, sizeof(int32_t));
			j = -1;
			while (++j < path_node->num_neighbors)
				ret = write(fd, &path_node->neighbors[j]->id, sizeof(uint32_t));
		}
	}
	(void)ret;
}

/*
** Writes patrol path info
** of npcs that might have them
*/

void			write_npc_patrol_path_information(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		j;
	int32_t		ret;
	t_npc		*npc;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type_npc)
		{
			npc = app->active_scene->objects[i]->params;
			ret = write(fd,
				&app->active_scene->objects[i]->id, sizeof(uint32_t));
			ret = write(fd, &npc->num_patrol_path_nodes, sizeof(int32_t));
			j = -1;
			while (++j < npc->num_patrol_path_nodes)
				if (npc->patrol_path[j])
					ret = write(fd, &npc->patrol_path[j]->id, sizeof(uint32_t));
				else
					ret = write(fd, 0, sizeof(uint32_t));
		}
	}
	(void)ret;
}

/*
** Writes key id info
*/

void			write_key_ids(int32_t fd, t_doom3d *app)
{
	int32_t		i;
	int32_t		ret;
	t_trigger	*trigger;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type_trigger)
		{
			trigger = app->active_scene->objects[i]->params;
			ret = write(fd,
				&app->active_scene->objects[i]->id, sizeof(uint32_t));
			ret = write(fd, &trigger->key_id, sizeof(uint32_t));
		}
	}
	(void)ret;
}
