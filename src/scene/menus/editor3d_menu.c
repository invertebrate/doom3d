/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 17:18:22 by ohakola          ###   ########.fr       */
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

static void			on_prefab_menu_button_click(t_button *self, void *params)
{
	(void)self;
	(void)params;
	ft_printf("Clicked prefab menu\n");
}

static void			on_objects_menu_button_click(t_button *self, void *params)
{
	(void)self;
	(void)params;
	ft_printf("Clicked objects menu\n");
}

static void			on_textures_menu_button_click(t_button *self, void *params)
{
	(void)self;
	(void)params;
	ft_printf("Clicked textures menu\n");
}

static void			on_normmaps_menu_button_click(t_button *self, void *params)
{
	(void)self;
	(void)params;
	ft_printf("Clicked normmaps menu\n");
}

static void			on_triggers_menu_button_click(t_button *self, void *params)
{
	(void)self;
	(void)params;
	ft_printf("Clicked triggers menu\n");
}

static void			on_enemies_menu_button_click(t_button *self, void *params)
{
	(void)self;
	(void)params;
	ft_printf("Clicked enemies menu\n");
}

static void			create_popup_menu(t_doom3d *app,
						t_editor_menu_index new_menu,
						t_button *self)
{
	t_button_group	*button_menu;
	t_vec2			pos;

	if (new_menu == editor_menu_prefabs)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[3]){
				"Prefab1", "Prefab2", "Hello there, love"},
			.num_buttons = 3,
			.on_click = on_prefab_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_objects)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[3]){
				"Prefab1", "Prefab2", "Hello there, love"},
			.num_buttons = 3,
			.on_click = on_objects_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_textures)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[3]){
				"Prefab1", "Prefab2", "Hello there, love"},
			.num_buttons = 3,
			.on_click = on_textures_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_normalmaps)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[3]){
				"Prefab1", "Prefab2", "Hello there, love"},
			.num_buttons = 3,
			.on_click = on_normmaps_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_triggers)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[3]){
				"Prefab1", "Prefab2", "Hello there, love"},
			.num_buttons = 3,
			.on_click = on_triggers_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else if (new_menu == editor_menu_enemies)
		button_menu = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[3]){
				"Prefab1", "Prefab2", "Hello there, love"},
			.num_buttons = 3,
			.on_click = on_enemies_menu_button_click,
			.button_font = app->window->debug_font,
		});
	else
		return ;
	ml_vector2_copy((t_vec2){self->pos[0] + self->width + 2,
		self->pos[1]}, pos);
	app->editor.editor_menu =
		button_popup_menu_create(button_menu, pos, (t_vec2){
		app->window->framebuffer->width, app->window->framebuffer->height},
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
			new_menu_id = editor_menu_prefabs;
		else if (self->id == 3)
			new_menu_id = editor_menu_objects;
		else if (self->id == 4)
			new_menu_id = editor_menu_textures;
		else if (self->id == 5)
			new_menu_id = editor_menu_normalmaps;
		else if (self->id == 6)
			new_menu_id = editor_menu_triggers;
		else if (self->id == 7)
			new_menu_id = editor_menu_enemies;
		create_or_open_popup_menu(app, new_menu_id, self);
	}
}

void				editor3d_menu_create(t_doom3d *app)
{
	app->active_scene->menus[0] = button_menu_create(app,
		(t_button_menu_params){
			.button_names = (const char*[8]){
				"Exit",
				"Save",
				"Prefabs",
				"Objects",
				"Textures",
				"NormMaps",
				"Triggers",
				"Enemies"
				},
			.num_buttons = 8,
			.on_click = on_editor_menu_button_click,
			.button_font = app->window->main_font,
		});
	app->active_scene->num_button_menus = 1;
}

