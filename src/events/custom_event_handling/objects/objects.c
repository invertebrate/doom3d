/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:32:02 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 22:59:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** 1. When this event is called, we add the object's index to
** objects_to_delete.
** 2. At the end of each frame objects set for deletion are deleted
** 3. After deletion, the index is saved to free_object_indices.
** 4. Free object indices is used first to add new objects, and if already used
** objects get added to the end of scene objects.
*/

void	handle_object_deletion(t_doom3d *app, t_3d_object *object)
{
	int32_t		i;
	int32_t		sum;

	deselect_object(app, object);
	i = -1;
	sum = (int32_t)(app->active_scene->num_objects
			+ app->active_scene->num_free_indices);
	while (++i < sum)
	{
		if (app->active_scene->objects[i] != NULL
			&& app->active_scene->objects[i]->id == object->id)
		{
			app->active_scene->objects_to_delete[
				app->active_scene->num_objects_to_delete++] = i;
			break ;
		}
	}
	if (app->active_scene->scene_id == scene_id_editor3d
		&& app->editor.num_selected_objects == 0)
		app->active_scene->menus[1]->is_active = false;
}

void	handle_object_scale(t_doom3d *app, t_3d_object *object,
					int32_t dir)
{
	(void)app;
	if (dir > 0)
		l3d_3d_object_scale(object, 1.1, 1.1, 1.1);
	else
		l3d_3d_object_scale(object, 1.0 / 1.1, 1.0 / 1.1, 1.0 / 1.1);
}

void	handle_object_scale_with_uvs(t_doom3d *app,
					t_3d_object *object,
					int32_t dir)
{
	(void)app;
	if (dir > 0)
		l3d_3d_object_scale_with_uvs(object, 1.1);
	else
		l3d_3d_object_scale_with_uvs(object, 1.0 / 1.1);
}

static void	toggle_shading_not_cull(t_3d_object *obj)
{
	if (obj->material->shading_opts & e_shading_dont_cull)
	{
		obj->material->shading_opts = (obj->material->shading_opts
				& ~(e_shading_dont_cull | e_shading_blue_highlight));
	}
	else
		l3d_object_set_shading_opts(obj,
			obj->material->shading_opts | e_shading_dont_cull);
}

void	handle_object_set_shading_not_cull(t_doom3d *app)
{
	int32_t		i;
	int32_t		count;
	t_3d_object	*obj;

	i = -1;
	count = 0;
	while (++i < app->editor.num_selected_objects)
	{
		obj = app->editor.selected_objects[i];
		if (obj && (obj->type == object_type_npc
				|| obj->type == object_type_default))
		{
			toggle_shading_not_cull(obj);
			count++;
		}
	}
	if (count++ > 0)
	{
		app->editor.is_saved = false;
		notify_user(app, (t_notification){
			.message = "Toggled selected objects distance cull mode",
			.time = 200, .type = notification_type_info});
		editor_objects_non_culled_highlight(app);
	}
}
