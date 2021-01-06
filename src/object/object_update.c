/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:48:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/06 16:00:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			object_type_to_str(t_3d_object *obj, char *str)
{
	if (obj->type == object_type_default)
		ft_sprintf(str, "%s", "3d-Object");
	else if (obj->type == object_type_npc)
		ft_sprintf(str, "%s", "NPC");
	else if (obj->type == object_type_trigger)
		ft_sprintf(str, "%s", "Trigger");
	else if (obj->type == object_type_projectile)
		ft_sprintf(str, "%s", "Projectile");
}

static void		handle_object_deletions(t_doom3d *app)
{
	int32_t		i;
	int32_t		del_index;
	t_bool		deleted_something;
	uint32_t	id;
	char		obj_type[128];

	i = -1;
	deleted_something = false;
	while (++i < (int32_t)app->active_scene->num_deleted)
	{
		del_index = app->active_scene->deleted_object_i[i];
		if (app->active_scene->objects[del_index] != NULL)
		{
			id = app->active_scene->objects[del_index]->id;
			object_type_to_str(app->active_scene->objects[del_index], obj_type);
			ft_printf("Deleted %s id, %u\n", obj_type, id);
			l3d_3d_object_destroy(app->active_scene->objects[del_index]);
			app->active_scene->objects[del_index] = NULL;
			deleted_something = true;
		}
	}
	if (deleted_something)
		active_scene_update_after_objects(app->active_scene);
}


void			doom3d_update_objects(t_doom3d *app)
{
	int32_t		i;

	handle_object_deletions(app);
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i])
		{
			
		}
	}
}