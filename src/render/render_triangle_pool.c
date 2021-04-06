/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_triangle_pool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:55:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/06 21:32:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Allocates space for render triangles which are reused every frame by
** renderer for rasterization
** Also allocates space for clipped vertices
*/

void		allocate_render_triangle_pool(t_doom3d *app)
{
	app->render_triangle_pool = NULL;
	app->render_triangle_pool =
		ft_calloc(sizeof(t_triangle) * RENDER_TRIANGLE_POOL_SIZE);
	error_check(!app->render_triangle_pool,
		"Failed to allocate render triangle pool");
	app->render_triangle_pool_size = RENDER_TRIANGLE_POOL_SIZE;
	app->num_render_triangles = 0;
	app->render_vertex_pool =
		ft_calloc(sizeof(t_vertex) * RENDER_VERTEX_POOL_SIZE);
	error_check(!app->render_vertex_pool,
		"Failed to allocate clipped vertices pool");
	app->num_render_vertices = 0;
	app->render_vertex_pool_size = RENDER_VERTEX_POOL_SIZE;
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

	if (app->num_render_vertices >= RENDER_VERTEX_POOL_SIZE)
	{
		LOG_FATAL("Too many render vertices %d >= RENDER_VERTEX_POOL_SIZE",
			app->num_render_vertices);
		exit(1);
	}
	vertex = app->render_vertex_pool + app->num_render_vertices;
	app->num_render_vertices++;
	return (vertex);
}

/*
** Returns a triangle from pool containing its own vertices
*/

t_triangle		*get_render_triangle_from_pool(t_doom3d *app)
{
	t_triangle	*render_triangle;

	if (app->num_render_triangles >= RENDER_TRIANGLE_POOL_SIZE)
	{
		LOG_FATAL("Too many render triangles %d,"
			" increase RENDER_TRIANGLE_POOL_SIZE or reduce triangles",
			app->num_render_triangles);
		exit(1);
	}
	render_triangle = app->render_triangle_pool + app->num_render_triangles;
	render_triangle->vtc[0] = get_vertex_from_pool(app);
	render_triangle->vtc[1] = get_vertex_from_pool(app);
	render_triangle->vtc[2] = get_vertex_from_pool(app);
	app->num_render_triangles++;
	return (render_triangle);
}
