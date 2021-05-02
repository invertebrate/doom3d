/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_parallel_work.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:33:20 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 21:59:11 by veilo            ###   ########.fr       */
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

	t_3d_object			*obj;
	t_ray				rays[2500];
	ft_memset(rays, 0, sizeof(t_ray) * 2500);

	work = params;
	last_pass = work->num_passes - 1;
	transparency_pass = 1;
	main_pass = 0;
	if (work->pass == main_pass)
	{
		clear_buffers(work);
		if (work->app->active_scene->scene_id == scene_id_editor3d)
			draw_editor_debug_grid(work);

		obj = work->app->active_scene->objects[0];
		if (obj)
		{
			t_sphere sphere;
			ml_vector3_set(sphere.forward, 0.0, 0.0, 1.0);
			ml_vector3_set(sphere.up, 0.0, -1.0, 0.0);
			ml_vector3_copy(obj->position, sphere.pos);
			sphere.radius = 10 * work->app->unit_size;
			cast_rays_sphere(rays, (uint32_t[2]){8, 8}, &sphere);
			for (int i = 0; i < 64; i++)
			{
				t_vec3	points[2];
				t_vec3	end_point;
				t_vec3	dir;

				ml_vector3_copy(rays[i].dir, dir);
				ml_vector3_mul(dir, sphere.radius, dir);
				ml_vector3_add(sphere.pos, dir, end_point);
				ml_vector3_copy(sphere.pos, points[0]);
				ml_vector3_copy(end_point, points[1]);
				if (i == 0)
				{
					draw_debug_line(work->app,
					work->framebuffer->sub_buffers[work->sub_buffer_i],
					points, 0xffff00ff);
				}
				else if (i == 49)
				{
					draw_debug_line(work->app,
					work->framebuffer->sub_buffers[work->sub_buffer_i],
					points, 0x0000ffff);
				}
				else
				{
					draw_debug_line(work->app,
					work->framebuffer->sub_buffers[work->sub_buffer_i],
					points, 0xffffffff);
				}
			}
		}
	}
	if (work->pass == main_pass)
		rasterize_triangles(work);
	else if (work->pass == transparency_pass)
		rasterize_triangles_transparent(work);
	if (work->app->active_scene->scene_id == scene_id_editor3d)
		render_editor_ux_highlights(work);
	if (work->pass == last_pass)
		draw_buffers_to_framebuffer(work);
	free(work);
}
