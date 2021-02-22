/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/16 14:30:09 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_delete_menu_button_click(t_button *self, void *params)
{
	t_doom3d			*app;
	t_3d_object			*object_to_delete;
	t_path_node			*delete;

	app = params;
	if (self->id == 0)
	{
		if (app->editor.selected_object)
		{
			if (app->editor.selected_object->type == object_type_path)
				delete_path_object_connections((delete = 
										app->editor.selected_object->params));
			object_to_delete = app->editor.selected_object;
			editor_deselect(app);
			object_set_for_deletion(app, object_to_delete);
			app->editor.is_saved = false;
			doom3d_notification_add(app, (t_notification){
			.message = "Deleted!",
			.type = notification_type_info, .time = 2000});
		}
	}
}

static void			on_editor_save(t_doom3d *app)
{
	if (!app->editor.is_saving)
	{
		editor_deselect(app);
		app->editor.is_saving = true;
		SDL_StartTextInput();
		doom3d_notification_add(app, (t_notification){
			.message = "Write name to save",
			.type = notification_type_info, .time = 2000});
	}
	else
	{
		doom3d_notification_add(app, (t_notification){
			.message = "Press enter to save",
			.type = notification_type_info, .time = 2000});
	}
}

static void			on_editor_exit(t_doom3d *app)
{
	app->next_scene_id = scene_id_main_menu;
	editor_deselect(app);
	SDL_StopTextInput();
	app->editor.is_saving = false;
}

static void			on_objects_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;
	t_vec3		pos;

	app = params;
	editor_place_position(app, pos);
	place_scene_object(app, (const char *[3]){self->text, NULL, NULL}, pos);
	active_scene_update_after_objects(app->active_scene);
	app->editor.is_saved = false;
	doom3d_notification_add(app, (t_notification){
			.message = "Placed object!",
			.type = notification_type_info, .time = 2000});
}

static void			on_textures_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (app->editor.selected_object)
	{
		app->editor.selected_object->material->texture =
			hash_map_get(app->active_scene->textures, (int64_t)self->text);
		hash_map_add(app->active_scene->object_textures,
			app->editor.selected_object->id, (void*)self->text);
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

static void			on_normmaps_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (app->editor.selected_object)
	{
		app->editor.selected_object->material->normal_map =
			hash_map_get(app->active_scene->normal_maps, (int64_t)self->text);
		hash_map_add(app->active_scene->object_normal_maps,
			app->editor.selected_object->id, (void*)self->text);
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

	editor_place_position(app, pos);
	model = l3d_plane_create(NULL, NULL);
	place_procedural_scene_object(app, model, (const char*[2]){
		"assets/textures/lava.bmp",
		"assets/textures/lava_normal.bmp"
	}, pos);
	l3d_3d_object_destroy(model);
}

static void			on_npc_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	uint32_t		npc_type;
	void			*get_res;
	t_vec3			pos;

	app = params;
	editor_place_position(app, pos);
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



static void			on_prefab_menu_button_click(t_button *self, void *params)
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

static void			on_trigger_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	uint32_t		trigger_type;
	void			*get_res;

	app = params;
	get_res = hash_map_get(app->active_scene->trigger_map,
		(int64_t)self->text);
	ft_memcpy(&trigger_type, &get_res, sizeof(uint32_t));
	if (trigger_type == trigger_player_start)
	{
		if (find_one_object_by_type(app, object_type_trigger, trigger_player_start))
			doom3d_notification_add(app, (t_notification){
			.message = "Player Start exists, delete it first!",
			.type = notification_type_info, .time = 2000});
		else
		{
			place_player_start(app);
			doom3d_notification_add(app, (t_notification){
			.message = "Placed Player Start!",
			.type = notification_type_info, .time = 2000});
			active_scene_update_after_objects(app->active_scene);
			app->editor.is_saved = false;
		}
	}
	else if (trigger_type == trigger_player_end)
	{
		if (find_one_object_by_type(app, object_type_trigger, trigger_player_end))
			doom3d_notification_add(app, (t_notification){
			.message = "Player End exists, delete it first!",
			.type = notification_type_info, .time = 2000});
		else
		{
			place_player_end(app);
			doom3d_notification_add(app, (t_notification){
			.message = "Placed Player End!",
			.type = notification_type_info, .time = 2000});
			active_scene_update_after_objects(app->active_scene);
			app->editor.is_saved = false;
		}
	}
	else if (trigger_type == trigger_weapon_drop_shotgun)
	{
		place_drop_shotgun(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placed shotgun trigger",
			.type = notification_type_info, .time = 2000});
		active_scene_update_after_objects(app->active_scene);
		app->editor.is_saved = false;
	}
	else if (trigger_type == trigger_item_jetpack)
	{
		place_drop_jetpack(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placed jetpack trigger",
			.type = notification_type_info, .time = 2000});
		active_scene_update_after_objects(app->active_scene);
		app->editor.is_saved = false;
	}
	else if (trigger_type == trigger_elevator_switch)
	{
		place_elevator_switch(app);
		doom3d_notification_add(app, (t_notification){
			.message = "Placed door/elevator switch",
			.type = notification_type_info, .time = 2000});
		active_scene_update_after_objects(app->active_scene);
		app->editor.is_saved = false;
	}
	editor_objects_invisible_highlight(app);
}

static void			on_light_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	t_3d_object		*light;
	t_vec3			pos;

	(void)self;
	app = params;
	editor_place_position(app, pos);
	place_scene_object(app, (const char*[3]){
		"assets/models/box.obj", NULL,  NULL}, pos);
	light = app->active_scene->objects[app->active_scene->last_object_index];
	l3d_object_set_shading_opts(light, e_shading_invisible);
	light->type = object_type_light;
	light->params_type = object_type_light;
	editor_objects_invisible_highlight(app);
}

static void			create_popup_menu(t_doom3d *app,
						t_editor_menu_index new_menu,
						t_button *self)
{
	t_button_group	*button_menu;
	t_vec2			pos;

	if (new_menu == editor_menu_objects)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.model_files,
			.num_buttons = app->active_scene->asset_files.num_models,
			.on_click = on_objects_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_textures)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.texture_files,
			.num_buttons = app->active_scene->asset_files.num_textures,
			.on_click = on_textures_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_normalmaps)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.normal_map_files,
			.num_buttons = app->active_scene->asset_files.num_normal_maps,
			.on_click = on_normmaps_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_prefabs)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.prefab_names,
			.num_buttons = app->active_scene->asset_files.num_prefabs,
			.on_click = on_prefab_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_npcs)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.npc_names,
			.num_buttons = app->active_scene->asset_files.num_npcs,
			.on_click = on_npc_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_triggers)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = app->active_scene->asset_files.trigger_names,
			.num_buttons = app->active_scene->asset_files.num_triggers,
			.on_click = on_trigger_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_lights)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[1]){"Light Source"},
			.num_buttons = 1,
			.on_click = on_light_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else
		return ;
	ml_vector2_copy((t_vec2){self->pos[0] + self->width + 2,
		self->pos[1]}, pos);
	app->editor.editor_menu =
		button_popup_menu_create(button_menu, pos, 3,
			(uint32_t[2]){CLEAR_COLOR, 0xffffffff});
}

static void			create_or_open_popup_menu(t_doom3d *app,
						t_editor_menu_index new_menu_id, t_button *self)
{
	if (app->editor.editor_menu_id != new_menu_id)
	{
		if (app->editor.editor_menu != NULL)
			button_popup_menu_destroy(app->editor.editor_menu);
		create_popup_menu(app, new_menu_id, self);
	}
	app->editor.editor_menu->is_open = true;
	app->editor.editor_menu_id = new_menu_id;
}

static void			on_editor_menu_button_click(t_button *self, void *params)
{
	t_doom3d			*app;
	t_editor_menu_index	new_menu_id;

	app = params;
	new_menu_id = editor_menu_none;
	if (self->id == 0)
		on_editor_exit(app);
	else if (self->id == 1)
		on_editor_save(app);
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
		create_or_open_popup_menu(app, new_menu_id, self);
	}
}

static void			on_new_level_menu_button_click(t_button *self, void *params)
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
		app->is_scene_reload = true;
		editor_init(app, app->editor.editor_level +
			app->num_levels - app->editor.editor_level);
	}
	else if (self->id == 0 && app->editor.editor_level == MAX_LEVELS)
		doom3d_notification_add(app, (t_notification){
			.message = "Too many levels created!!",
			.type = notification_type_info, .time = 2000});
}

void				editor3d_menu_create(t_doom3d *app)
{
	error_check(!(app->active_scene->menus =
		ft_calloc(sizeof(t_button_group*) * 3)), "Failed to malloc menus");
	app->active_scene->menus[0] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[9]){
				"Exit",
				"Save",
				"Objects",
				"Textures",
				"NormMaps",
				"Prefabs",
				"Characters",
				"Triggers",
				"Lights"},
			.num_buttons = 9,
			.on_click = on_editor_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->menus[1] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[1]){
				"Delete"},
			.num_buttons = 1,
			.on_click = on_delete_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->menus[2] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[1]){
				"New"},
			.num_buttons = 1,
			.on_click = on_new_level_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->num_button_menus = 3;
}

