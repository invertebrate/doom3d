/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_update_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 22:37:09 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 12:41:49 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	delete_object_by_index(t_doom3d *app, t_3d_object **objects,
					int32_t del_index)
{
	uint32_t	id;
	char		obj_type[128];

	id = objects[del_index]->id;
	object_type_to_str(objects[del_index], obj_type);
	if (objects[del_index]->type == object_type_npc)
	{
		npc_destroy(objects[del_index]);
		if (app->settings.is_debug)
			LOG_DEBUG("Deleted object %s, id %u that may have"
				"3D animations", obj_type, id);
	}
	else
	{
		l3d_3d_object_destroy(objects[del_index]);
		if (app->settings.is_debug)
			LOG_DEBUG("Deleted object %s, id %u", obj_type, id);
	}
}

/*
** Delete objects that have been set for during the frame
*/

void	delete_objects_set_for_deletion(t_doom3d *app)
{
	int32_t		i;
	int32_t		del_index;
	t_3d_object	**objects;

	objects = app->active_scene->objects;
	l3d_temp_objects_destroy_if_expired(&app->active_scene->temp_objects);
	i = -1;
	while (++i < (int32_t)app->active_scene->num_deleted)
	{
		del_index = app->active_scene->deleted_object_i[i];
		if (objects[del_index] != NULL)
		{
			delete_object_by_index(app, objects, del_index);
			objects[del_index] = NULL;
		}
	}
}

t_bool	should_update_npc_state(t_doom3d *app)
{
	static uint32_t	old_time;
	uint32_t		new_time;
	t_bool			update_npcs;

	new_time = SDL_GetTicks();
	if (!old_time)
		old_time = 0;
	app->active_scene->npc_update_timer += new_time - old_time;
	update_npcs = false;
	if (app->active_scene->npc_update_timer > 250)
	{
		app->active_scene->npc_update_timer -= 250;
		update_npcs = true;
		old_time = new_time;
	}
	return (update_npcs);
}

t_bool	object_has_forces(t_3d_object *obj)
{
	return (obj->type == object_type_npc);
}
