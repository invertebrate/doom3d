/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 21:02:30 by veilo             #+#    #+#             */
/*   Updated: 2021/04/29 21:23:44 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_3d_object		*find_object_by_id(t_doom3d *app, uint32_t id)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->id == id)
			return (app->active_scene->objects[i]);
	}
	return (NULL);
}

t_3d_object		*find_one_object_by_type(t_doom3d *app, uint32_t object_type,
					uint32_t param_type)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] &&
			app->active_scene->objects[i]->type == object_type &&
			app->active_scene->objects[i]->params_type == param_type)
			return (app->active_scene->objects[i]);
	}
	return (NULL);
}

void			object_type_to_str(t_3d_object *obj, char *str)
{
	if (obj->type == object_type_default)
		ft_sprintf(str, "%s", "Object");
	else if (obj->type == object_type_npc)
		ft_sprintf(str, "%s", "NPC");
	else if (obj->type == object_type_trigger)
		ft_sprintf(str, "%s", "Trigger");
	else if (obj->type == object_type_projectile)
		ft_sprintf(str, "%s", "Projectile");
	else if (obj->type == object_type_light)
		ft_sprintf(str, "%s", "Light");
	else if (obj->type == object_type_path)
		ft_sprintf(str, "%s", "Path");
}

void			extend_all_objects_shading_opts(t_doom3d *app,
					t_shading_opts opts_to_add)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
		if (app->active_scene->objects[i])
		{
			l3d_object_set_shading_opts(app->active_scene->objects[i],
				app->active_scene->objects[i]->material->shading_opts |
					opts_to_add);
		}
}

void			remove_all_objects_shading_opts(t_doom3d *app,
					t_shading_opts opts_to_remove)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
		if (app->active_scene->objects[i])
		{
			if (app->active_scene->objects[i]->material->shading_opts &
				opts_to_remove)
			{
				l3d_object_set_shading_opts(app->active_scene->objects[i],
				app->active_scene->objects[i]->material->shading_opts ^
					opts_to_remove);
			}
		}
}
