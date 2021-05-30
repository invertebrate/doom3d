/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_clip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/27 21:22:59 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	push_two_clipped_triangles(t_doom3d *app,
					t_tri_vec *render_triangles,
					t_triangle *clipped_triangles[2])
{
	screen_intersection(app, clipped_triangles[0]);
	screen_intersection(app, clipped_triangles[1]);
	update_triangle_vertex_zvalues(clipped_triangles[0], app->unit_size);
	update_triangle_vertex_zvalues(clipped_triangles[1], app->unit_size);
	l3d_triangle_update(clipped_triangles[0]);
	l3d_triangle_update(clipped_triangles[1]);
	l3d_triangle_vec_push(render_triangles, clipped_triangles[0]);
	l3d_triangle_vec_push(render_triangles, clipped_triangles[1]);
}

static void	push_one_clipped_triangle(t_doom3d *app,
					t_tri_vec *render_triangles,
					t_triangle *clipped_triangles[2])
{
	screen_intersection(app, clipped_triangles[0]);
	update_triangle_vertex_zvalues(clipped_triangles[0], app->unit_size);
	l3d_triangle_update(clipped_triangles[0]);
	l3d_triangle_vec_push(render_triangles, clipped_triangles[0]);
}

static void	push_non_clipped_triangle(t_doom3d *app,
					t_tri_vec *render_triangles,
					t_triangle *triangle)
{
	t_triangle	*render_triangle;

	render_triangle = get_render_triangle_from_pool(app);
	l3d_triangle_copy(render_triangle, triangle);
	screen_intersection(app, render_triangle);
	update_triangle_vertex_zvalues(render_triangle, app->unit_size);
	l3d_triangle_update(render_triangle);
	l3d_triangle_vec_push(render_triangles, render_triangle);
}

static void	set_clipped_triangles(t_doom3d *app,
					t_triangle *clipped_triangles[2],
					t_triangle *triangle)
{
	clipped_triangles[0] = get_render_triangle_from_pool(app);
	clipped_triangles[1] = get_render_triangle_from_pool(app);
	l3d_triangle_copy(clipped_triangles[0], triangle);
	l3d_triangle_copy(clipped_triangles[1], triangle);
	l3d_init_clipped_triangles(clipped_triangles);
}

/*
** If triangle is to be clipped, clipped triangles are added to render
** triangle vector. If not clipped, just add the inputted triangle to
** render triangles vector
*/

void	clip_and_add_to_render_triangles(t_doom3d *app,
					t_tri_vec **render_triangles,
					t_triangle *triangle)
{
	t_triangle	*clipped_triangles[2];
	int32_t		test_clip;
	t_plane		near;
	t_tri_vec	*render_vec;

	set_clipped_triangles(app, clipped_triangles, triangle);
	ml_vector3_copy((t_vec3){0, 0, NEAR_CLIP_DIST}, near.origin);
	ml_vector3_copy((t_vec3){0, 0, Z_DIR}, near.normal);
	near.d = NEAR_CLIP_DIST;
	test_clip = l3d_clip_triangle(triangle, &near, clipped_triangles);
	if (!(triangle->material->shading_opts & e_shading_transparent))
		render_vec = render_triangles[0];
	else
		render_vec = render_triangles[1];
	if (test_clip == 2)
		push_two_clipped_triangles(app, render_vec, clipped_triangles);
	else if (test_clip == 1)
		push_one_clipped_triangle(app, render_vec, clipped_triangles);
	else
		push_non_clipped_triangle(app, render_vec, triangle);
}
