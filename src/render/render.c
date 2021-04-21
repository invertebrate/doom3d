/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:09:05 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/19 00:44:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Render editor 3d view. It gets a little special treatment as the view
** should not cover whole framebuffer, but instead just a portion of it leaving
** space for the UI. Basically it's the same as the main game, but just uses
** a smaller framebuffer.
*/
void			render_parallel_editor_3d_view(t_doom3d *app)
{

	render_parallel_3d_view(app, app->window->editor_framebuffer);
	l3d_image_place(&(t_surface){.pixels = app->window->framebuffer->buffer,
			.w = app->window->framebuffer->width,
			.h = app->window->framebuffer->height},
		&(t_surface){.pixels = app->window->editor_framebuffer->buffer,
			.w = app->window->editor_framebuffer->width,
			.h = app->window->editor_framebuffer->height},
			(int32_t[2]){app->window->editor_pos[0],
				app->window->editor_pos[1]} ,1.0);
}

/*
** Render everything in app to framebuffer including 3d and UI.
** 1. Render parallel
*/
void			render_to_framebuffer(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
		render_parallel_3d_view(app, app->window->framebuffer);
	else if (app->active_scene->scene_id == scene_id_editor3d)
		render_parallel_editor_3d_view(app);
	render_ui(app);
	if (app->is_debug)
		render_debug_info(app);
}
