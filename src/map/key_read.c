/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 02:04:38 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 02:45:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static int32_t	read_key_if_object_exists(t_doom3d *app, char *contents,
					int32_t offset)
{
	uint32_t	object_id;
	t_trigger	*trigger;
	int32_t		key_id;
	t_3d_object	*obj;

	trigger = NULL;
	ft_memcpy(&object_id, contents + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	obj = find_object_by_id(app, object_id);
	if (obj)
	{
		trigger = obj->params;
		ft_memcpy(&key_id, contents + offset, sizeof(int32_t));
		trigger->key_id = key_id;
	}
	offset += sizeof(int32_t);
	return (offset);
}

/*
** Reads trigger key id information
** and sets the correct key id values
*/

int32_t			read_key_id_information(t_doom3d *app, char *contents)
{
	int32_t		offset;
	int32_t		num_triggers;
	int32_t		i;

	offset = 0;
	num_triggers = 0;
	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		if (app->active_scene->objects[i]->type == object_type_trigger)
			num_triggers++;
	i = -1;
	while (++i < num_triggers)
		offset = read_key_if_object_exists(app, contents, offset);
	return (offset);
}
