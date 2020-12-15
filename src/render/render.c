/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:09:05 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/15 19:25:01 by ohakola          ###   ########.fr       */
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

static void		draw_buffers(t_render_work *work)
{
	t_sub_framebuffer	*sub_buffer;
	t_framebuffer		*framebuffer;
	t_surface			frame;
	t_surface			sub_frame;
	int32_t				xy[0];

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
	clear_buffers(work);
	rasterize_triangles(work);
	draw_buffers(work);
	free(work);
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

static void		render_work_parallel(t_doom3d *app, t_framebuffer *framebuffer)
{
	int32_t				i;
	t_render_work		*work;
	t_tri_vec			*render_triangles;

	update_camera(app);
	render_triangles = prepare_render_triangles(app);
	app->triangles_in_view = render_triangles->size;
	i = -1;
	while (++i < framebuffer->num_x * framebuffer->num_y)
	{
		error_check(!(work = malloc(sizeof(*work))),
			"Failed to malloc rasterize work");
		work->framebuffer = framebuffer;
		work->sub_buffer_i = i;
		work->app = app;
		work->render_triangles = render_triangles;
		thread_pool_add_work(app->thread_pool, render_work, work);
	}
	thread_pool_wait(app->thread_pool);
	destroy_render_triangles(render_triangles);
	app->is_first_render = false;
}

void			render_editor_3d_view(t_doom3d *app)
{

	render_work_parallel(app, app->window->editor_framebuffer);
	l3d_image_place(&(t_surface){.pixels = app->window->framebuffer->buffer,
			.w = app->window->framebuffer->width,
			.h = app->window->framebuffer->height},
		&(t_surface){.pixels = app->window->editor_framebuffer->buffer,
			.w = app->window->editor_framebuffer->width,
			.h = app->window->editor_framebuffer->height},
			(int32_t[2]){app->window->editor_pos[0],
				app->window->editor_pos[1]} ,1.0);
}

void			doom3d_render(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_main_game)
	{
		render_work_parallel(app, app->window->framebuffer);
	}
	else if (app->active_scene->scene_id == scene_id_editor)
	{
		render_editor_3d_view(app);
	}
	ui_render(app);
}
