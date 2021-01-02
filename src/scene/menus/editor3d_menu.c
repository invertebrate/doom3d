/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 19:28:29 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_editor_save(t_doom3d *app)
{
	if (!app->editor.is_saving)
	{
		editor_deselect(app);
		app->editor.is_saving = true;
		SDL_StartTextInput();
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

	app = params;
	place_object(app, (const char *[3]){self->text, NULL, NULL},
		(t_vec3){0, 0, 0});
	active_scene_update_after_objects(app->active_scene);
	app->editor.is_saved = false;
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
	}
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
		create_or_open_popup_menu(app, new_menu_id, self);
	}
}

void				editor3d_menu_create(t_doom3d *app)
{
	app->active_scene->menus[0] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[5]){
				"Exit",
				"Save",
				"Objects",
				"Textures",
				"NormMaps"},
			.num_buttons = 5,
			.on_click = on_editor_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->num_button_menus = 1;
}

