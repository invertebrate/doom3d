/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:48:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/06 18:30:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

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
			ft_printf("Deleted %s, id %u\n", obj_type, id);
			l3d_3d_object_destroy(app->active_scene->objects[del_index]);
			app->active_scene->objects[del_index] = NULL;
			deleted_something = true;
		}
	}
	if (deleted_something &&
		app->active_scene->scene_id == scene_id_editor3d)
		active_scene_update_after_objects(app->active_scene);
}

static t_bool	should_update_npcs(t_doom3d *app)
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

static void		update_object_by_type(t_doom3d *app, t_3d_object *obj,
					t_bool is_npc_update)
{
	if (obj->type == object_type_npc)
	{
		if (is_npc_update)
			npc_update(app, obj);
		npc_execute_behavior(app, obj);
	}
	//update animation
}

void			doom3d_update_objects(t_doom3d *app)
{
	int32_t			i;
	t_bool			is_npc_update;
	t_3d_object		*obj;

	if (app->active_scene->scene_id == scene_id_main_game ||
		app->active_scene->scene_id == scene_id_editor3d)
		handle_object_deletions(app);
	if (app->active_scene->is_paused ||
		app->active_scene->scene_id != scene_id_main_game)
		return ;
	is_npc_update = should_update_npcs(app);
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		update_object_by_type(app, obj, is_npc_update);
	}
	active_scene_update_after_objects(app->active_scene);
}