/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:09:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:54:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static int32_t	read_trigger_links_by_num_links(t_doom3d *app, char *contents,
					t_trigger *trigger,
					int32_t num_trigger_links)
{
	int32_t		j;
	int32_t		k;
	uint32_t	object_id;
	t_3d_object	*obj;
	int32_t		offset;

	offset = 0;
	j = -1;
	k = 0;
	while (++j < num_trigger_links)
	{
		ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
		offset += sizeof(uint32_t);
		obj = find_object_by_id(app, object_id);
		if (obj && trigger)
			trigger->linked_obj[k++] = obj;
	}
	return (offset);
}

int32_t			read_trigger_links(t_doom3d *app,
					char *contents, int32_t offset)
{
	t_3d_object	*obj;
	uint32_t	object_id;
	int32_t		num_trigger_links;
	t_trigger	*trigger;

	trigger = NULL;
	num_trigger_links = 0;
	ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	obj = find_object_by_id(app, object_id);
	if (obj)
	{
		trigger = obj->params;
		ft_memcpy(&num_trigger_links, contents + offset, sizeof(int32_t));
		trigger->num_links = num_trigger_links;
	}
	offset += sizeof(int32_t);
	offset += read_trigger_links_by_num_links(app, contents,
		trigger, num_trigger_links);
	return (offset);
}

/*
** Reads trigger link information
** and links the triggers to their linked objects
*/

int32_t			read_trigger_link_information(t_doom3d *app, char *contents)
{
	int32_t		offset;
	int32_t		num_npcs;
	int32_t		i;

	offset = 0;
	num_npcs = get_num_npcs(app);
	i = -1;
	while (++i < num_npcs)
		offset = read_trigger_links(app, contents, offset);
	return (offset);
}
