/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_parallel_work.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:33:20 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 23:47:33 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		clear_buffers(t_render_work *work)
{
	t_sub_framebuffer	*sub_buffer;

	sub_buffer = work->framebuffer->sub_buffers[work->sub_buffer_i];
	l3d_buffer_uint32_clear(sub_buffer->buffer,
		sub_buffer->width * sub_buffer->height, 0x000000FF);
	l3d_buffer_float_clear(sub_buffer->zbuffer,
		sub_buffer->width * sub_buffer->height, FLT_MAX);
}

static void		draw_buffers_to_framebuffer(t_render_work *work)
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

static void		render_editor_ux_highlights(t_render_work *work)
{
	uint32_t	last_pass;

	last_pass = work->num_passes - 1;
	path_draw_connections(work);
	if (work->app->editor.num_selected_objects > 0)
	{
		draw_selected_wireframe(work);
		draw_selected_enemies_direction(work);
		if (work->app->editor.num_selected_objects == 1 &&
			work->app->editor.selected_objects[0]->type == object_type_npc)
			patrol_path_highlight(work);
	}
	else if (work->pass == last_pass)
		draw_editor_placement_position(work);
}

void			player_debug_graphic_draw(t_render_work *work)
{
	t_doom3d	*app;
	t_player	player;
	app = work->app;
	player = app->player;
	for (int i = 0; i < COLLIDER_RAY_TOTAL; i++)
	{
		t_vec3	points[2];
		t_vec3	end_point;
		t_vec3	dir;

		ml_vector3_copy(player.collider.rays[i].dir, dir);
		ml_vector3_mul(dir, player.collider.sphere.radius, dir);
		ml_vector3_add(player.collider.sphere.pos, dir, end_point);
		ml_vector3_copy(player.collider.sphere.pos, points[0]);
		ml_vector3_copy(end_point, points[1]);
		if (ml_vector3_angle_deg(player.collider.rays[i].dir, (t_vec3){0.0, 1.0, 0.0})
			< SLOPE_ANGLE_THRESHOLD)
		{
			draw_debug_line(app,
			work->framebuffer->sub_buffers[work->sub_buffer_i],
			points, 0x000fffff);
		}
		else
		{
			draw_debug_line(app,
			work->framebuffer->sub_buffers[work->sub_buffer_i],
			points, 0xffffffff);
		}
	}
	(void)app;
}

/*
** The render work inside each thread (square of framebuffer).
** First we clear buffers, then depending on passes & scenes, render rest
*/

void			render_work(void *params)
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
	if (work->pass == last_pass && work->app->active_scene->scene_id
		== scene_id_main_game
		&& work->app->is_third_person)
		draw_aabb(work->app, work->framebuffer->sub_buffers[work->sub_buffer_i],
			&work->app->player.aabb, 0xff0000ff);
		//function draws player debug graphic^
	player_debug_graphic_draw(work);
	if (work->pass == last_pass)
		draw_buffers_to_framebuffer(work);
	free(work);
}
