/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:13:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 20:47:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	get_editor_savename(t_doom3d *app, char *filename)
{
	if (app->editor.is_saving)
	{
		if (ft_strlen(app->editor.editor_savename) == 0)
			ft_sprintf(filename, "File: %s", "NULL");
		else
			ft_sprintf(filename, "File: %s", app->editor.editor_savename);
	}
	else
	{
		if (ft_strlen(app->editor.editor_filename) == 0)
			ft_sprintf(filename, "File: %s", "NULL");
		else
			ft_sprintf(filename, "File: %s", app->editor.editor_filename);
	}
}

static void	draw_unsaved_underline(t_doom3d *app, char *filename,
					uint32_t color)
{
	int32_t		width;
	int32_t		i;

	TTF_SizeText(app->window->small_font, filename, &width, NULL);
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

static void	render_saved_filename(t_doom3d *app)
{
	char		filename[256];
	uint32_t	rgba[4];
	uint32_t	color;

	if (app->editor.is_saved)
		color = 0x00ff00ff;
	else
		color = 0xff0000ff;
	l3d_u32_to_rgba(color, rgba);
	get_editor_savename(app, filename);
	window_text_render_shaded(app->window, (t_text_params){
		.text = filename, .blend_ratio = 1.0,
		.xy = (int [2]){10, app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->small_font);
	if (app->editor.is_saving)
		draw_unsaved_underline(app, filename, color);
}

void	render_guide_on_popup(t_doom3d *app)
{
	char	guide[1024];

	set_guide_text(guide);
	window_text_render_wrapped_shaded(app->window, (t_text_params){
		.text = guide, .blend_ratio = 1.0,
		.xy = (int [2]){app->editor.editor_menu->pos[0] + 10,
		app->editor.editor_menu->pos[1] + 10},
		.text_color = (SDL_Color){0, 255, 0, 255}}, app->window->small_font);
}

void	render_editor_ui(t_doom3d *app)
{
	render_button_menu(app->active_scene->menus[0], (t_vec2){10, 0});
	render_button_menu(app->active_scene->menus[2],
		(t_vec2){app->active_scene->menus[0]->max_width - 40,
		app->active_scene->menus[0]->buttons[0]->pos[1]});
	render_button_menu(app->active_scene->menus[3], (t_vec2){
		10, app->window->framebuffer->height - 100});
	if (app->active_scene->menus[1]->is_active)
		render_button_menu(app->active_scene->menus[1], (t_vec2){
			app->active_scene->menus[0]->max_width - 40,
			app->window->framebuffer->height - 100});
	render_saved_filename(app);
	render_object_information(app);
	if (app->editor.editor_menu != NULL)
	{
		button_popup_menu_clamp_position_to_window(app->editor.editor_menu,
			&app->mouse);
		button_popup_menu_render(app->window, app->editor.editor_menu);
		if (app->editor.editor_menu_id == editor_menu_guide
			&& app->editor.editor_menu->is_open)
			render_guide_on_popup(app);
	}
}
