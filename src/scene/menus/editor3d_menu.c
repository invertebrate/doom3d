/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 15:57:24 by ohakola          ###   ########.fr       */
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

static void			on_editor_menu_button_click(t_button *self, void *params)
{
	t_doom3d		*app;
	t_button_group	*button_menu;
	t_vec2			pos;

	app = params;
	if (self->id == 0)
		on_editor_exit(app);
	else if (self->id == 1)
		on_editor_save(app);
	else
	{
		if (app->editor.editor_menu != NULL)
		{
			button_popup_menu_destroy(app->editor.editor_menu);
			app->editor.editor_menu_open = editor_menu_none;
			app->editor.editor_menu = NULL;
		}
	}
	if (self->id == 2)
	{
		app->editor.editor_menu_open = editor_menu_prefabs;
		button_menu = button_menu_create(app, (const char*[3]){
		"Test1", "Test2", "Hello there, love"}, 3, on_prefab_menu_button_click);
		ml_vector2_copy((t_vec2){self->pos[0] + self->width + 2, self->pos[1]},
			pos);
		app->editor.editor_menu =
			button_popup_menu_create(button_menu, pos, (t_vec2){
			app->window->framebuffer->width, app->window->framebuffer->height},
			(uint32_t[2]){CLEAR_COLOR, 0xffffffff});
		app->editor.editor_menu->is_open = true;
	}
	if (self->id == 3)
		app->editor.editor_menu_open = editor_menu_objects;
	if (self->id == 4)
		app->editor.editor_menu_open = editor_menu_textures;
	if (self->id == 5)
		app->editor.editor_menu_open = editor_menu_normalmaps;
	if (self->id == 6)
		app->editor.editor_menu_open = editor_menu_triggers;
	if (self->id == 7)
		app->editor.editor_menu_open = editor_menu_enemies;
}

void				editor3d_menu_create(t_doom3d *app)
{
	app->active_scene->menus[0] = button_menu_create(app, (const char*[8]){
		"Exit",
		"Save",
		"Prefabs",
		"Objects",
		"Textures",
		"NormMaps",
		"Triggers",
		"Enemies"
		}, 8, on_editor_menu_button_click);
	app->active_scene->num_menu_buttons = 1;
}

