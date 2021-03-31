/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:13:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 17:25:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		get_editor_savename(t_doom3d *app, char *filename)
{
	if (app->editor.is_saving)
		ft_sprintf(filename, "File: %s",
			ft_strlen(app->editor.editor_savename) == 0 ? "NULL" :
				app->editor.editor_savename);
	else
		ft_sprintf(filename, "File: %s",
			ft_strlen(app->editor.editor_filename) == 0 ? "NULL" :
				app->editor.editor_filename);
}

static void		draw_unsaved_underline(t_doom3d *app, char *filename,
					uint32_t color)
{
	int32_t		width;
	int32_t		i;

	TTF_SizeText(app->window->debug_font, filename, &width, NULL);
	i = -1;
	while (++i < 4)
		l3d_line_draw(app->window->framebuffer->buffer,
		(uint32_t[2]){app->window->framebuffer->width,
			app->window->framebuffer->height},
		(int32_t[2][2]){{10,
			app->window->framebuffer->height - 5 + i},
			{10 + width,
			app->window->framebuffer->height - 5 + i}},
			color);
}

static void		editor_info_render(t_doom3d *app)
{
	char		filename[256];
	uint32_t	rgba[4];
	uint32_t	color;

	color = app->editor.is_saved ? 0x00ff00ff : 0xff0000ff;
	l3d_u32_to_rgba(color, rgba);
	get_editor_savename(app, filename);
	window_text_render(app->window, (t_text_params){
		.text = filename, .blend_ratio = 1.0,
		.xy = (int[2]){10, app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->debug_font);
	if (app->editor.is_saving)
		draw_unsaved_underline(app, filename, color);
	if (app->editor.num_selected_objects > 0)
		window_text_render(app->window, (t_text_params){
			.text = app->editor.selected_object_str, .blend_ratio = 1.0,
			.xy = (int[2]){app->window->framebuffer->width - 200,
				app->window->framebuffer->height - 30},
			.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
			app->window->debug_font);
}

static void		editor_object_location_render(t_doom3d *app)
{
	char		str[256];
	uint32_t	rgba[4];
	uint32_t	color;

	if (app->editor.num_selected_objects != 1)
		return ;
	color = app->editor.is_saved ? 0x00ff00ff : 0xff0000ff;
	l3d_u32_to_rgba(color, rgba);
	ft_memset(str, 0, sizeof(str));
	ft_sprintf(str, "pos: [%.2f, %.2f, %.2f]",
		app->editor.selected_objects[0]->position[0] / app->unit_size,
		app->editor.selected_objects[0]->position[1] / app->unit_size,
		app->editor.selected_objects[0]->position[2] / app->unit_size
	);
	window_text_render(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int[2]){app->window->framebuffer->width / 4,
			app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->debug_font);
	ft_sprintf(str, "scale: [%.2f, %.2f, %.2f]",
		app->editor.selected_objects[0]->scale[0][0] / app->unit_size,
		app->editor.selected_objects[0]->scale[1][1] / app->unit_size,
		app->editor.selected_objects[0]->scale[2][2] / app->unit_size);
	window_text_render(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int[2]){app->window->framebuffer->width / 4 + 200,
			app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->debug_font);
	ft_sprintf(str, "unit_size: %.2f", app->unit_size);
	window_text_render(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int[2]){app->window->framebuffer->width / 4 + 400,
			app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->debug_font);
}

void		render_guide_on_popup(t_doom3d *app)
{
	char	guide[1024];

	ft_sprintf(guide,
		"Tab: Switch to next level in level list\n"
		"Ctrl + Tab: Switch to previous level in level list\n"
		"Button W | A | S | D: Move & Strafe\n"
		"Mouse Middle / Alt + Mouse Move: Rotate view\n"
		"Mouse Left: Select Target by mouse\n"
		"Mouse Left + Shift: Select Multiple By mouse\n"
		"Mouse Right on target: Deselect one\n"
		"Mouse Right on empty: Deselect All\n"
		"Mouse Right on path node: Connect to another node\n"
		"Button R + X | Y | Z: Rotate selected\n"
		"Button Right | Left | Up | Down: Move selected on x and z axis\n"
		"Button O | L: Move selected target on y axis\n"
		"Button [ | ]: Scale selected\n"
		"Button =/+ | -: Inc/Decrement patrol path node slot\n");
	window_text_render_wrapped(app->window, (t_text_params){
			.text = guide, .blend_ratio = 1.0,
			.xy = (int[2]){app->editor.editor_menu->pos[0] + 10,
				app->editor.editor_menu->pos[1] + 10},
			.text_color = (SDL_Color){0, 255, 0, 255}},
			app->window->debug_font);
}

void		editor_ui_render(t_doom3d *app)
{
	button_menu_render(app->active_scene->menus[0], (t_vec2){10, 0});
	button_menu_render(app->active_scene->menus[2],
		(t_vec2){app->active_scene->menus[0]->buttons[0]->width - 20,
			app->active_scene->menus[0]->buttons[0]->pos[1]});
	button_menu_render(app->active_scene->menus[3], (t_vec2){
		10, app->window->framebuffer->height - 100});
	if (app->active_scene->menus[1]->is_active)
		button_menu_render(app->active_scene->menus[1], (t_vec2){
			app->active_scene->menus[0]->buttons[0]->width - 20,
			app->window->framebuffer->height - 100});
	if (app->editor.editor_menu != NULL)
	{
		button_popup_menu_render(app->window, app->editor.editor_menu);
		if (app->editor.editor_menu_id == editor_menu_guide &&
			app->editor.editor_menu->is_open)
			render_guide_on_popup(app);
	}
	editor_info_render(app);
	editor_object_location_render(app);
}
