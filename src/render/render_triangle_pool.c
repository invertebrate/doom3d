/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_triangle_pool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:55:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 20:33:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Allocates space for render triangles which are reused every frame by
** renderer for rasterization
** Also allocates space for clipped vertices
*/
void		allocate_render_triangle_pool(t_doom3d *app,
				uint32_t size)
{
	app->render_triangle_pool = NULL;
	app->render_triangle_pool_size = size;
	app->render_triangle_pool =
		ft_calloc(sizeof(t_triangle) * app->render_triangle_pool_size);
	error_check(!app->render_triangle_pool,
		"Failed to allocate render triangle pool");
	app->num_render_triangles = 0;
	app->render_vertex_pool_size = size * 3;
	app->render_vertex_pool =
		ft_calloc(sizeof(t_vertex) * app->render_vertex_pool_size);
	error_check(!app->render_vertex_pool,
		"Failed to allocate clipped vertices pool");
	app->num_render_vertices = 0;
}

/*
** At each frame we reset the number of render triangles so we can reuse
** the pool
*/
void			reset_render_triangle_pool(t_doom3d *app)
{
	app->num_render_triangles = 0;
	app->num_render_vertices = 0;
}

/*
** Free the triangles in pool
*/
void			destroy_render_triangle_pool(t_doom3d *app)
{
	free(app->render_triangle_pool);
	app->render_triangle_pool = NULL;
	app->render_triangle_pool_size = 0;
	app->num_render_triangles = 0;
	free(app->render_vertex_pool);
	app->render_vertex_pool = NULL;
	app->num_render_vertices = 0;
	app->render_vertex_pool_size = 0;
}

static t_vertex	*get_vertex_from_pool(t_doom3d *app)
{
	t_vertex	*vertex;

	vertex = app->render_vertex_pool + app->num_render_vertices;
	app->num_render_vertices++;
	return (vertex);
}

/*
** Returns a triangle from pool containing its own vertices.
** Reallocates if size is too small.
*/
t_triangle		*get_render_triangle_from_pool(t_doom3d *app)
{
	t_triangle	*render_triangle;
	uint32_t	render_triangle_pool_size;

	if (app->num_render_triangles >= app->render_triangle_pool_size)
	{
		render_triangle_pool_size = app->render_vertex_pool_size;
		LOG_INFO("Reallocating render pool: %d to %d",
			app->render_triangle_pool_size,
			app->render_triangle_pool_size * 2);
		destroy_render_triangle_pool(app);
		allocate_render_triangle_pool(app, render_triangle_pool_size * 2);
	}
	render_triangle = app->render_triangle_pool + app->num_render_triangles;
	render_triangle->vtc[0] = get_vertex_from_pool(app);
	render_triangle->vtc[1] = get_vertex_from_pool(app);
	render_triangle->vtc[2] = get_vertex_from_pool(app);
	app->num_render_triangles++;
	return (render_triangle);
}
