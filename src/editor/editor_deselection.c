/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_deselection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 01:17:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 01:18:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Deselect a single object
*/

void			deselect_object(t_doom3d *app, t_3d_object *delete_object)
{
	t_3d_object		*selected_objects[MAX_SELECTED_OBJECTS];
	int32_t			i;
	int32_t			j;
	t_3d_object		*match_obj;

	i = -1;
	j = 0;
	while (++i < app->editor.num_selected_objects)
	{
		if (delete_object->id != app->editor.selected_objects[i]->id)
			selected_objects[j++] = app->editor.selected_objects[i];
		else
		{
			match_obj = app->editor.selected_objects[i];
			match_obj->material->shading_opts =
				(match_obj->material->shading_opts & ~(e_shading_select));
			app->editor.selected_objects[i] = NULL;
		}
	}
	app->editor.num_selected_objects = j;
	j = -1;
	while (++j < app->editor.num_selected_objects)
	{
		app->editor.selected_objects[j] = selected_objects[j];
	}
}

/*
** Deselect all or one object depending on where mouse hits
*/

void			editor_deselect(t_doom3d *app)
{
	t_3d_object		*hit_obj;

	hit_obj = editor_object_by_mouse(app);
	if (hit_obj)
		deselect_object(app, hit_obj);
	else
	{
		if (app->editor.num_selected_objects > 0)
			notify_user(app, (t_notification){
			.message = "Deselected all!",
			.type = notification_type_info, .time = 2000});
		editor_deselect_all(app);
	}
}

/*
** Deslect all objects in editor
*/

void			editor_deselect_all(t_doom3d *app)
{
	int32_t		i;
	t_3d_object	*obj;

	i = -1;
	while (++i < (int32_t)(app->editor.num_selected_objects))
	{
		obj = app->editor.selected_objects[i];
		obj->material->shading_opts = (obj->material->shading_opts &
			~(e_shading_select));
		app->editor.selected_objects[i] = NULL;
	}
	app->editor.num_selected_objects = 0;
	app->editor.selected_object_str[0] = '\0';
}
