/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:09:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/29 12:55:22 by ahakanen         ###   ########.fr       */
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

static int32_t	get_num_triggers(t_doom3d *app)
{
	int32_t		num_triggers;
	int32_t		i;

	num_triggers = 0;
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_trigger)
			num_triggers++;
	return (num_triggers);
}

/*
** Reads trigger link information
** and links the triggers to their linked objects
*/

int32_t			read_trigger_link_information(t_doom3d *app, char *contents)
{
	int32_t		offset;
	int32_t		num_triggers;
	int32_t		i;

	offset = 0;
	num_triggers = get_num_triggers(app);
	i = -1;
	while (++i < num_triggers)
		offset = read_trigger_links(app, contents, offset);
	return (offset);
}
