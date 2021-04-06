/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:09:05 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/06 19:21:00 by ohakola          ###   ########.fr       */
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

static void		render_work(void *params)
{
	t_render_work		*work;

	work = params;
	// Grid should be first, so draw on pass 0
	if (work->pass == 0)
	{
		clear_buffers(work);
		if (work->app->active_scene->scene_id == scene_id_editor3d)
			draw_editor_debug_grid(work);
	}
	if (work->pass == 0)
		rasterize_triangles(work);
	else if (work->pass == 1)
		rasterize_triangles_transparent(work);
	// Draw debug lines
	if (work->app->active_scene->scene_id == scene_id_editor3d)
	{
		path_draw_connections(work);
		if (work->app->editor.num_selected_objects > 0)
		{
			draw_selected_wireframe(work);
			draw_selected_enemies_direction(work);
			if (work->app->editor.num_selected_objects == 1 &&
				work->app->editor.selected_objects[0]->type == object_type_npc)
				patrol_path_highlight(work);
		}
		// Draw placement cursor only on last pass
		else if (work->pass == work->num_passes - 1)
			draw_editor_placement_position(work);
	}
	else if (work->app->active_scene->scene_id == scene_id_main_game)
	{
		draw_npc_dirs(work);
	}
	// Draw buffers only on last pass
	if (work->pass == work->num_passes - 1)
		draw_buffers_to_framebuffer(work);
	free(work);
}

static void		render_pass(t_doom3d *app, t_framebuffer *framebuffer,
					t_tri_vec **render_triangles, uint32_t pass_num_passes[2])
{
	int32_t				i;
	t_render_work		*work;

	i = -1;
	while (++i < framebuffer->num_x * framebuffer->num_y)
	{
		error_check(!(work = ft_calloc(sizeof(*work))),
			"Failed to malloc rasterize work");
		work->framebuffer = framebuffer;
		work->sub_buffer_i = i;
		work->app = app;
		work->num_passes = pass_num_passes[1];
		work->pass = pass_num_passes[0];
		work->render_triangles = work->pass == 0 ? render_triangles[0] :
			render_triangles[1];
		thread_pool_add_work(app->thread_pool, render_work, work);
	}
}

/*
** This is the main render function containing the "flow" of the render pipeline
** 1. Update camera (view boxes)
** 2. Prepare render triangles, it basically outputs a vector of triangles
** to be rendered. A small subset filtered out of all scene object triangles.
** Some triangles are clipped if they intersect with near plane. Those clipped
** triangles are separately allocated in the render triangles. Profiling has
** shown that the preparation is rather fast despite allocation. Most work is
** in rasterization.
** 3. Each sub buffer gets a reference to the render triangles and rasterizes
** those triangles. A sub buffer is a portion of pixels in the screen.
** Render work clears sub buffers, rasterizes and lastly draws onto the main
** framebuffer.
** 4. Parallel work is waited to finish and render triangles are destroyed.
*/

static void		render_parallel(t_doom3d *app, t_framebuffer *framebuffer)
{

	t_tri_vec			**render_triangles;
	uint32_t			num_passes;

	update_camera(app);
	uint64_t	start = performance_counter_start();
	render_triangles = prepare_render_triangles(app);
	app->triangles_in_view = render_triangles[0]->size +
		render_triangles[1]->size;
	performance_counter_end(start, "Prepare triangles", 0.0);
	if (render_triangles[1]->size > 0)
		num_passes = 2;
	else
		num_passes = 1;
	start = performance_counter_start();
	render_pass(app, framebuffer, render_triangles,
		(uint32_t[2]){0, num_passes});
	thread_pool_wait(app->thread_pool);
	performance_counter_end(start, "Render pass 1", 0.0);
	// Transparency pass
	if (num_passes == 2)
	{
		start = performance_counter_start();
		render_pass(app, framebuffer, render_triangles,
		(uint32_t[2]){1, num_passes});
		thread_pool_wait(app->thread_pool);
		performance_counter_end(start, "Render pass 2", 0.0);
	}
	start = performance_counter_start();	
	destroy_render_triangle_vecs(render_triangles);
	performance_counter_end(start, "Destroy render tris", 0.0);
}

void			render_editor_3d_view(t_doom3d *app)
{

	render_parallel(app, app->window->editor_framebuffer);
	l3d_image_place(&(t_surface){.pixels = app->window->framebuffer->buffer,
			.w = app->window->framebuffer->width,
			.h = app->window->framebuffer->height},
		&(t_surface){.pixels = app->window->editor_framebuffer->buffer,
			.w = app->window->editor_framebuffer->width,
			.h = app->window->editor_framebuffer->height},
			(int32_t[2]){app->window->editor_pos[0],
				app->window->editor_pos[1]} ,1.0);
}

void			render_to_framebuffer(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		render_parallel(app, app->window->framebuffer);
	}
	else if (app->active_scene->scene_id == scene_id_editor3d)
	{
		render_editor_3d_view(app);
	}
	ui_render(app);
	if (app->is_debug)
		render_debug_info(app);
}
