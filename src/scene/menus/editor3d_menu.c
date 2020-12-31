/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/31 15:26:16 by ohakola          ###   ########.fr       */
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

static void			on_editor_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
		on_editor_exit(app);
	if (self->id == 1)
		on_editor_save(app);
	if (self->id == 2)
		app->editor.editor_menu_open = editor_menu_prefabs;
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
	app->active_scene->num_menus = 1;
}

