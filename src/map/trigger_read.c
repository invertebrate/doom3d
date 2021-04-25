/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:09:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:20:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Reads trigger link information
** and links the triggers to their linked objects
*/

int32_t		read_trigger_link_information(t_doom3d *app, char *contents)
{
	int32_t		offset;
	uint32_t	object_id;
	t_3d_object	*obj;
	t_trigger	*trigger;
	int32_t		num_npcs;
	int32_t		num_patrol_path_nodes;
	int32_t		i;
	int32_t		j;
	int32_t		k;

	offset = 0;
	num_npcs = 0;
	trigger = NULL;
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_trigger)
			num_npcs++;
	i = -1;
	while (++i < num_npcs)
	{
		num_patrol_path_nodes = 0;
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		if (obj) {
			trigger = obj->params;
			ft_memcpy(&num_patrol_path_nodes, contents + offset, sizeof(int32_t));
			trigger->num_links = num_patrol_path_nodes;
		}
		offset += sizeof(int32_t);
		j = -1;
		k = 0;
		while (++j < num_patrol_path_nodes)
		{
			ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
			offset += sizeof(uint32_t);
			obj = find_object_by_id(app, object_id);
			if (obj && trigger)
				trigger->linked_obj[k++] = obj;
		}
	}
	return (offset);
}
