/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:46:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 01:20:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Select an object in editor
*/

void			select_object(t_doom3d *app, t_3d_object *object)
{
	char	object_type[128];
	int32_t	i;

	i = -1;
	while (++i < app->editor.num_selected_objects)
	{
		if (app->editor.selected_objects[i]->id == object->id)
			return ;
	}
	if (app->editor.num_selected_objects >= MAX_SELECTED_OBJECTS)
	{
		notify_user(app, (t_notification){.message = "Can't select more!",
			.type = notification_type_info, .time = 2000});
		return ;
	}
	app->editor.selected_objects[app->editor.num_selected_objects++] = object;
	object->material->shading_opts |= e_shading_select;
	if (app->editor.num_selected_objects == 1)
	{
		object_type_to_str(object, object_type);
		ft_sprintf(app->editor.selected_object_str, "%s: %u", object_type,
			object->id);
	}
	else
		ft_sprintf(app->editor.selected_object_str, "multiple");
}

static void		path_connect_selection(t_doom3d *app, t_3d_object *new)
{
	t_3d_object	*old;

	old = NULL;
	if (app->editor.selected_objects[0])
		old = app->editor.selected_objects[0];
	editor_deselect_all(app);
	select_object(app, new);
	if (old->type == object_type_path && new->type == object_type_path)
		path_objects_set_neighbour(app, old);
	if (old->type == object_type_npc && new->type == object_type_path)
		patrol_path_link_node(new, old, app->editor.patrol_slot);
	if (old->type == object_type_trigger && new->type == object_type_npc)
		trigger_link_object_to_npc(old, new);
	if ((!old && new->type == object_type_trigger) || new == old)
		trigger_update_key_id(app, new);
}

/*
** Cast ray from player to mouse world position (on screen)
** and see which closest triangle intersects.
** Add hit object to selected object.
*/

void			editor_select_by_mouse(t_doom3d *app)
{
	t_3d_object		*hit_obj;

	hit_obj = editor_object_by_mouse(app);
	if (hit_obj)
	{
		if (app->keyboard.state[SDL_SCANCODE_LCTRL])
			path_connect_selection(app, hit_obj);
		else if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
			select_object(app, hit_obj);
		else
		{
			editor_deselect_all(app);
			select_object(app, hit_obj);
		}
	}
}
