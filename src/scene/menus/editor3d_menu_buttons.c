/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu_buttons.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/30 18:17:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			on_delete_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	(void)self;
	app = params;
	doom3d_push_event(app, event_editor_delete, NULL, NULL);
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
	t_doom3d	*app;
	t_vec3		pos;

	app = params;
	editor_pos_camera_front(app, pos);
	place_scene_object(app, (const char *[3]){self->text, NULL, NULL}, pos);
	active_scene_update_after_objects(app->active_scene);
	app->editor.is_saved = false;
	doom3d_notification_add(app, (t_notification){
			.message = "Placed object!",
			.type = notification_type_info, .time = 2000});
}

void			on_textures_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;
	int32_t		i;
	t_surface	*texture;

	app = params;
	if (app->editor.num_selected_objects > 0)
	{
		texture =
			hash_map_get(app->active_scene->textures, (int64_t)self->text);
		i = -1;
		while (++i < app->editor.num_selected_objects)
		{
			app->editor.selected_objects[i]->material->texture = texture;
			hash_map_add(app->active_scene->object_textures,
				app->editor.selected_objects[i]->id, (void*)self->text);
		}
		app->editor.is_saved = false;
		doom3d_notification_add(app, (t_notification){
			.message = "Texture set!",
			.type = notification_type_info, .time = 2000});
	}
	else
	{
		doom3d_notification_add(app, (t_notification){
			.message = "Select object first!",
			.type = notification_type_info, .time = 2000});
	}	
}

void			on_normmaps_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;
	int32_t		i;
	t_surface	*normmap;

	app = params;
	if (app->editor.num_selected_objects > 0)
	{
		normmap =
			hash_map_get(app->active_scene->normal_maps, (int64_t)self->text);
		i = -1;
		while (++i < app->editor.num_selected_objects)
		{
			app->editor.selected_objects[i]->material->normal_map = normmap;
			hash_map_add(app->active_scene->object_normal_maps,
				app->editor.selected_objects[i]->id, (void*)self->text);
		}
		app->editor.is_saved = false;
		doom3d_notification_add(app, (t_notification){
			.message = "Normal map set!",
			.type = notification_type_info, .time = 2000});
	}
	else
	{
		doom3d_notification_add(app, (t_notification){
			.message = "Select object first!",
			.type = notification_type_info, .time = 2000});
	}
}

static void			prefab_spawn_plane(t_doom3d *app)
{
	t_3d_object		*model;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	model = l3d_plane_create(NULL, NULL);
	place_procedural_scene_object(app, model, (const char*[2]){
		"assets/textures/lava.bmp",
		"assets/textures/lava_normal.bmp"
	}, pos);
	l3d_3d_object_destroy(model);
}

void			on_npc_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	uint32_t		npc_type;
	void			*get_res;
	t_vec3			pos;

	app = params;
	editor_pos_camera_front(app, pos);
	get_res = hash_map_get(app->active_scene->npc_map,
		(int64_t)self->text);
	ft_memcpy(&npc_type, &get_res, sizeof(uint32_t));
	npc_spawn(app, pos, 0, npc_type);
	active_scene_update_after_objects(app->active_scene);
	app->editor.is_saved = false;
	doom3d_notification_add(app, (t_notification){
			.message = "Placed npc!",
			.type = notification_type_info, .time = 2000});
}



void			on_prefab_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	uint32_t		prefab_type;
	void			*get_res;

	app = params;
	get_res = hash_map_get(app->active_scene->prefab_map,
		(int64_t)self->text);
	ft_memcpy(&prefab_type, &get_res, sizeof(uint32_t));
	if (prefab_type == (uint32_t)prefab_plane)
	{
		prefab_spawn_plane(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placed plane!",
			.type = notification_type_info, .time = 2000});
	}
	else if (prefab_type == (uint32_t)prefab_path_node)
	{
		place_path_object(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placed Path Node!",
			.type = notification_type_info, .time = 2000});
		editor_objects_invisible_highlight(app);
	}
	active_scene_update_after_objects(app->active_scene);
	app->editor.is_saved = false;
}

void			on_trigger_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	uint32_t		trigger_type;
	void			*get_res;

	app = params;
	get_res = hash_map_get(app->active_scene->trigger_map,
		(int64_t)self->text);
	ft_memcpy(&trigger_type, &get_res, sizeof(uint32_t));
	if (trigger_type == trigger_player_start)
		doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_trigger, (void*)trigger_player_start);
	else if (trigger_type == trigger_player_end)
		doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_trigger, (void*)trigger_player_end);
	else if (trigger_type == trigger_weapon_drop_shotgun)
		doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_trigger, (void*)trigger_weapon_drop_shotgun);
	else if (trigger_type == trigger_item_jetpack)
		doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_trigger, (void*)trigger_item_jetpack);
	else if (trigger_type == trigger_item_key)
		doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_trigger, (void*)trigger_item_key);
	else if (trigger_type == trigger_elevator_switch)
		doom3d_push_event(app, event_editor_start_placement,
			(void*)object_type_trigger, (void*)trigger_elevator_switch);
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
