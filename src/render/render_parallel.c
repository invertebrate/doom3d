/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_parallelization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 00:30:18 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/19 00:43:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Parallel render pass creating work or each thread (square part of screen)
*/
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
void			render_parallel_3d_view(t_doom3d *app, t_framebuffer *framebuffer)
{

	t_tri_vec			**render_triangles;
	uint32_t			num_passes;
	uint32_t			transparency_pass;

	transparency_pass = 2;
	update_camera(app);
	render_triangles = prepare_render_triangles(app);
	app->triangles_in_view = render_triangles[0]->size +
		render_triangles[1]->size;
	if (render_triangles[1]->size > 0)
		num_passes = transparency_pass;
	else
		num_passes = 1;
	render_pass(app, framebuffer, render_triangles,
		(uint32_t[2]){0, num_passes});
	thread_pool_wait(app->thread_pool);
	if (num_passes == transparency_pass)
	{
		render_pass(app, framebuffer, render_triangles,
		(uint32_t[2]){1, num_passes});
		thread_pool_wait(app->thread_pool);
	}
	destroy_render_triangle_vecs(render_triangles);
}
