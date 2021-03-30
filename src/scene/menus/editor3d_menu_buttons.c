/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu_buttons.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 01:02:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			on_delete_menu_button_click(t_button *self, void *params)
{
	(void)self;
	doom3d_push_event(params, event_editor_delete, NULL, NULL);
}

void			on_editor_save_button_click(t_doom3d *app)
{
	doom3d_push_event(app, event_editor_start_save, NULL, NULL);
}

void			on_editor_exit_button_click(t_doom3d *app)
{
	doom3d_push_event(app, event_editor_exit, NULL, NULL);
}

void			on_objects_menu_button_click(t_button *self, void *params)
{
	doom3d_push_event(params, event_editor_start_placement,
		(void*)object_type_default, (void*)self->text);
}

void			on_textures_menu_button_click(t_button *self, void *params)
{
	doom3d_push_event(params, event_editor_add_texture, (void*)self->text, NULL);
}

void			on_normmaps_menu_button_click(t_button *self, void *params)
{
	doom3d_push_event(params, event_editor_add_normal_map, (void*)self->text,
		NULL);
}

void			on_npc_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;

	app = params;
	doom3d_push_event(app, event_editor_start_placement,
		(void*)object_type_npc, hash_map_get(app->active_scene->npc_map,
		(int64_t)self->text));
}

void			on_prefab_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;

	app = params;
	doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_default,
			hash_map_get(app->active_scene->prefab_map,
		(int64_t)self->text));
}

void			on_trigger_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	void			*get_res;

	app = params;
	get_res = hash_map_get(app->active_scene->trigger_map,
		(int64_t)self->text);
	doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_trigger, get_res);
}

void			on_light_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;

	(void)self;
	app = params;
	doom3d_push_event(app, event_editor_start_placement,
		(void*)object_type_light, NULL);
}

void			on_editor_menu_button_click(t_button *self, void *params)
{
	t_doom3d			*app;
	t_editor_menu_index	new_menu_id;

	app = params;
	new_menu_id = editor_menu_none;
	if (self->id == 0)
		on_editor_exit_button_click(app);
	else if (self->id == 1)
		on_editor_save_button_click(app);
	else
	{
		if (self->id == 2)
			new_menu_id = editor_menu_objects;
		else if (self->id == 3)
			new_menu_id = editor_menu_textures;
		else if (self->id == 4)
			new_menu_id = editor_menu_normalmaps;
		else if (self->id == 5)
			new_menu_id = editor_menu_prefabs;
		else if (self->id == 6)
			new_menu_id = editor_menu_npcs;
		else if (self->id == 7)
			new_menu_id = editor_menu_triggers;
		else if (self->id == 8)
			new_menu_id = editor_menu_lights;
		doom3d_push_event(app, event_editor_open_popup_menu,
			(void*)new_menu_id, (void*)self->pos);
	}
}

void			on_new_level_menu_button_click(t_button *self, void *params)
{
	t_doom3d			*app;

	app = params;
	if (self->id == 0 && app->editor.editor_level < MAX_LEVELS)
	{
		if (!app->level_list[app->editor.editor_level])
		{
			doom3d_notification_add(app, (t_notification){
				.message =
					"Save map first, and add it to assets/level_list.txt!!",
				.type = notification_type_info, .time = 2000});
			return ;
		}
		editor_init(app, app->editor.editor_level +
			app->num_levels - app->editor.editor_level);
		doom3d_push_event(app, event_scene_reload, NULL, NULL);
	}
	else if (self->id == 0 && app->editor.editor_level == MAX_LEVELS)
		doom3d_notification_add(app, (t_notification){
			.message = "Too many levels created!!",
			.type = notification_type_info, .time = 2000});
}
