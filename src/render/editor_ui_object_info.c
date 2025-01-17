/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ui_object_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 23:00:50 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/12 09:34:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	render_object_position(t_doom3d *app, char *str,
					uint32_t rgba[4])
{
	ft_sprintf(str, "pos: [%.2f, %.2f, %.2f]",
		app->editor.selected_objects[0]->position[0] / app->unit_size,
		app->editor.selected_objects[0]->position[1] / app->unit_size,
		app->editor.selected_objects[0]->position[2] / app->unit_size);
	window_text_render_shaded(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int [2]){app->window->framebuffer->width / 4,
		app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->small_font);
}

static void	render_object_scale(t_doom3d *app, char *str,
					uint32_t rgba[4])
{
	ft_sprintf(str, "scale: [%.2f, %.2f, %.2f]",
		app->editor.selected_objects[0]->scale[0][0] / app->unit_size,
		app->editor.selected_objects[0]->scale[1][1] / app->unit_size,
		app->editor.selected_objects[0]->scale[2][2] / app->unit_size);
	window_text_render_shaded(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int [2]){app->window->framebuffer->width / 4 + 200,
		app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->small_font);
}

uint32_t	get_render_color(t_doom3d *app)
{
	uint32_t	color;

	color = 0xff0000ff;
	if (app->editor.is_saved)
		color = 0x00ff00ff;
	return (color);
}

void	render_object_information(t_doom3d *app)
{
	char		str[256];
	uint32_t	rgba[4];
	uint32_t	color;

	if (app->editor.num_selected_objects != 1)
		return ;
	color = get_render_color(app);
	l3d_u32_to_rgba(color, rgba);
	ft_memset(str, 0, sizeof(str));
	render_object_position(app, str, rgba);
	render_object_scale(app, str, rgba);
	ft_sprintf(str, "unit_size: %.2f", app->unit_size);
	window_text_render_shaded(app->window, (t_text_params){
		.text = str, .blend_ratio = 1.0,
		.xy = (int [2]){app->window->framebuffer->width / 4 + 400,
		app->window->framebuffer->height - 30},
		.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
		app->window->small_font);
	if (app->editor.num_selected_objects > 0)
		window_text_render_shaded(app->window, (t_text_params){
			.text = app->editor.selected_object_str, .blend_ratio = 1.0,
			.xy = (int [2]){app->window->framebuffer->width - 200,
			app->window->framebuffer->height - 30},
			.text_color = (SDL_Color){rgba[0], rgba[1], rgba[2], rgba[3]}},
			app->window->small_font);
}
