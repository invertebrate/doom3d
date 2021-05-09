/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_parallel_work.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:33:20 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/09 21:10:00 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	clear_buffers(t_render_work *work)
{
	t_sub_framebuffer	*sub_buffer;

	sub_buffer = work->framebuffer->sub_buffers[work->sub_buffer_i];
	l3d_buffer_uint32_clear(sub_buffer->buffer,
		sub_buffer->width * sub_buffer->height, 0x000000FF);
	l3d_buffer_float_clear(sub_buffer->zbuffer,
		sub_buffer->width * sub_buffer->height, FLT_MAX);
}

static void	draw_buffers_to_framebuffer(t_render_work *work)
{
	t_sub_framebuffer	*sub_buffer;
	t_framebuffer		*framebuffer;
	t_surface			frame;
	t_surface			sub_frame;
	int32_t				xy[2];

	sub_buffer = work->framebuffer->sub_buffers[work->sub_buffer_i];
	framebuffer = work->framebuffer;
	frame.w = framebuffer->width;
	frame.h = framebuffer->height;
	frame.pixels = framebuffer->buffer;
	sub_frame.w = sub_buffer->width;
	sub_frame.h = sub_buffer->height;
	sub_frame.pixels = sub_buffer->buffer;
	xy[0] = sub_buffer->x_start;
	xy[1] = sub_buffer->y_start;
	l3d_image_place(&frame, &sub_frame, xy, 1.0);
}

/*
** Renders visual information inside editor such as wireframes, patrol path
** connections or selection highlights.
*/

static void	render_editor_ux_highlights(t_render_work *work)
{
	uint32_t	last_pass;

	last_pass = work->num_passes - 1;
	path_draw_connections(work);
	if (work->app->editor.num_selected_objects > 0)
	{
		draw_selected_wireframe(work);
		draw_selected_enemies_direction(work);
		if (work->app->editor.num_selected_objects == 1
			&& work->app->editor.selected_objects[0]->type == object_type_npc)
			patrol_path_highlight(work);
	}
	else if (work->pass == last_pass)
		draw_editor_placement_position(work);
}

static void	draw_third_person(t_render_work *work)
{
	if (work->pass == work->num_passes - 1
		&& work->app->active_scene->scene_id == scene_id_main_game
		&& work->app->is_third_person)
	{
		draw_aabb(work->app, work->framebuffer->sub_buffers[work->sub_buffer_i],
			&work->app->player.aabb, 0xff0000ff);
	}
}
/*
** The render work inside each thread (square of framebuffer).
** First we clear buffers, then depending on passes & scenes, render rest
*/

void	render_work(void *params)
{
	t_render_work		*work;
	uint32_t			last_pass;
	uint32_t			main_pass;
	uint32_t			transparency_pass;

	work = params;
	last_pass = work->num_passes - 1;
	transparency_pass = 1;
	main_pass = 0;
	if (work->pass == main_pass)
	{
		clear_buffers(work);
		if (work->app->active_scene->scene_id == scene_id_editor3d)
			draw_editor_debug_grid(work);
	}
	if (work->pass == main_pass)
		rasterize_triangles(work);
	else if (work->pass == transparency_pass)
		rasterize_triangles_transparent(work);
	if (work->app->active_scene->scene_id == scene_id_editor3d)
		render_editor_ux_highlights(work);
	draw_third_person(work);
	if (work->pass == last_pass)
		draw_buffers_to_framebuffer(work);
	free(work);
}
