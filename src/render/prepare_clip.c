/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_clip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/14 18:15:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Sets z value for triangle vertices. Unit size division is used to bring
** the number to a more reasonable range - to be more standard for rasterizer
** and e.g. depth shading.
*/

static void		update_triangle_vertex_zvalues(t_triangle *triangle,
					float unit_size)
{
	triangle->vtc_zvalue[0] = 1.0 /
		(triangle->vtc[0]->pos[2] / unit_size + L3D_EPSILON);
	triangle->vtc_zvalue[1] = 1.0 /
		(triangle->vtc[1]->pos[2] / unit_size + L3D_EPSILON);
	triangle->vtc_zvalue[2] = 1.0 /
		(triangle->vtc[2]->pos[2] / unit_size + L3D_EPSILON);
}

static void		add_two_clipped_triangles(t_doom3d *app,
					t_tri_vec *render_triangles,
					t_triangle clipped_triangles[2])
{
	ft_printf("Adding two clipped triangles %d\n", SDL_GetTicks());
	l3d_triangle_update(&clipped_triangles[0]);
	l3d_triangle_update(&clipped_triangles[1]);
	screen_intersection(app, &clipped_triangles[0]);
	screen_intersection(app, &clipped_triangles[1]);
	update_triangle_vertex_zvalues(&clipped_triangles[0], app->unit_size);
	update_triangle_vertex_zvalues(&clipped_triangles[1], app->unit_size);
	l3d_triangle_vec_push(render_triangles,
		l3d_triangle_copy(&clipped_triangles[0], true));
	l3d_triangle_vec_push(render_triangles,
		l3d_triangle_copy(&clipped_triangles[1], true));
}

static void		add_one_clipped_triangles(t_doom3d *app,
					t_tri_vec *render_triangles,
					t_triangle clipped_triangles[2])
{
	ft_printf("Adding one clipped triangles %d\n", SDL_GetTicks());
	l3d_triangle_update(&clipped_triangles[0]);
	screen_intersection(app, &clipped_triangles[0]);
	update_triangle_vertex_zvalues(&clipped_triangles[0], app->unit_size);
	l3d_triangle_vec_push(render_triangles,
		l3d_triangle_copy(&clipped_triangles[0], true));
}

/*
** If triangle is to be clipped, clipped triangles are added to render
** triangle vector. If not clipped, just add the inputted triangle to
** render triangles vector
*/

void			clip_and_add_to_render_triangles(t_doom3d *app,
					t_tri_vec *render_triangles,
					t_triangle *triangle)
{
	t_triangle	clipped_triangles[2];
	t_vertex	vtc[6];
	int32_t		test_clip;

	l3d_set_clipped_triangles(vtc, triangle, clipped_triangles);
	test_clip = l3d_clip_triangle(triangle,
		&app->active_scene->main_camera->screen, clipped_triangles);
	if (test_clip == 2)
		add_two_clipped_triangles(app, render_triangles, clipped_triangles);
	else if (test_clip == 1)
		add_one_clipped_triangles(app, render_triangles, clipped_triangles);
	else
	{
		screen_intersection(app, triangle);
		update_triangle_vertex_zvalues(triangle, app->unit_size);
		l3d_triangle_vec_push(render_triangles,
			l3d_triangle_copy(triangle, true));
	}
}
