/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/29 15:47:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		ui_title_render(t_doom3d *app)
{
	window_text_render_centered(app->window, (t_text_params){
			.text = "Doom-3D", .blend_ratio = 1.0,
			.xy = (int[2]){app->window->framebuffer->width / 2,
				FONT_SIZE * 2 + 10},
			.text_color = (SDL_Color){255, 0, 0, 255}},
			app->window->title_font);
}

void			framebuffer_dark_overlay(t_framebuffer *framebuffer,
					int32_t width, int32_t height, t_vec2 pos)
{
	uint32_t	dark[width * height];
	int32_t		i;

	i = -1;
	while (++i < width * height)
		dark[i] = 0x000000FF;
	l3d_image_place(&(t_surface){.pixels = framebuffer->buffer,
			.h = framebuffer->height, .w = framebuffer->width},
		&(t_surface){.pixels = dark, .w = width, .h = height},
		(int32_t[2]){pos[0], pos[1]}, 0.5);
}

void			menu_render(t_button_group *menu, t_vec2 pos)
{
	if (menu == NULL)
		return ;
	if (pos[0] != menu->pos[0] || pos[1] != menu->pos[1])
	{
		button_group_update_position(menu, pos);
	}
	button_group_render(menu);
}

void			editor_filename_render(t_doom3d *app)
{
	char		filename[256];
	uint32_t	rgba[4];
	int32_t		width;
	int32_t		i;
	uint32_t	color;

	color = app->editor.is_saved ? 0x00ff00ff : 0xff0000ff;
	l3d_u32_to_rgba(color, rgba);
	if (app->editor.is_saving)
		ft_sprintf(filename, "File: %s",
			ft_strlen(app->editor.editor_savename) == 0 ? "NULL" :
				app->editor.editor_savename);
	else
		ft_sprintf(filename, "File: %s",
			ft_strlen(app->editor.editor_filename) == 0 ? "NULL" :
				app->editor.editor_filename);
	window_text_render(app->window, (t_text_params){
		.text = filename, .blend_ratio = 1.0,
		.xy = (int[2]){10, app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->debug_font);
	if (app->editor.is_saving)
	{
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
}

void			editor_object_location_render(t_doom3d *app)
{
	char		pos_str[256];
	t_vec3		pos;
	uint32_t	rgba[4];
	uint32_t	color;

	if (!app->editor.selected_object)
		return ;
	color = app->editor.is_saved ? 0x00ff00ff : 0xff0000ff;
	l3d_u32_to_rgba(color, rgba);
	ft_memset(pos_str, 0, sizeof(pos_str));
	ml_vector3_copy((t_vec3){
		app->editor.selected_object->position[0] / app->unit_size,
		app->editor.selected_object->position[1] / app->unit_size,
		app->editor.selected_object->position[2] / app->unit_size,
	}, pos);
	ft_sprintf(pos_str, "pos: [%.2f, %.2f, %.2f]", pos[0], pos[1], pos[2]);
	window_text_render(app->window, (t_text_params){
		.text = pos_str, .blend_ratio = 1.0,
		.xy = (int[2]){app->window->framebuffer->width / 4,
			app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->debug_font);
}

void			ui_render(t_doom3d *app)
{


	if (app->active_scene->scene_id == scene_id_main_menu ||
		app->active_scene->scene_id == scene_id_main_menu_settings)
	{
		ui_title_render(app);
		menu_render(app->active_scene->menus[0], (t_vec2){100,
			app->window->framebuffer->height / 2 -
			app->active_scene->menus[0]->buttons[0]->height *
				app->active_scene->menus[0]->num_buttons / 2});
	}
	else if (app->active_scene->scene_id == scene_id_main_game)
	{
		hud_render(app);
		if (app->active_scene->is_paused)
		{
			framebuffer_dark_overlay(app->window->framebuffer,
				app->window->framebuffer->width,
					app->window->framebuffer->height, (t_vec2){0, 0});
			menu_render(app->active_scene->menus[0], (t_vec2){100,
				app->window->framebuffer->height / 2 -
				app->active_scene->menus[0]->buttons[0]->height *
					app->active_scene->menus[0]->num_buttons / 2});
		}
	}
	else if (app->active_scene->scene_id == scene_id_editor3d)
	{
		menu_render(app->active_scene->menus[0], (t_vec2){10, 0});
		editor_filename_render(app);
		editor_object_location_render(app);
		if (app->editor.selected_object)
			window_text_render(app->window, (t_text_params){
				.text = app->editor.selected_object_str, .blend_ratio = 1.0,
				.xy = (int[2]){app->window->framebuffer->width - 390,
					app->window->framebuffer->height - 30},
				.text_color = (SDL_Color){0, 255, 0, 255}},
				app->window->debug_font);
	}
}

void			loading_render(t_doom3d *app)
{
	ui_title_render(app);
	window_text_render_centered(app->window, (t_text_params){
		.text = "Loading",
		.blend_ratio = 1.0,
		.xy = (int32_t[2]){app->window->framebuffer->width / 2,
			app->window->framebuffer->height / 2},
		.text_color = (SDL_Color){255, 255, 255, 255}},
		app->window->main_font);
}
