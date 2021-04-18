/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 23:51:19 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 23:52:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"


void			destroy_render_triangle_vecs(t_tri_vec **render_triangles)
{
	l3d_triangle_vec_delete(render_triangles[0]);
	l3d_triangle_vec_delete(render_triangles[1]);
	free(render_triangles);
}

static t_box3d	origo_centered_world_box(t_doom3d *app)
{
	t_box3d				centered_world;
	int32_t				i;

	ft_memcpy(&centered_world,
		&app->active_scene->triangle_tree->root->bounding_box,
		sizeof(t_box3d));
	i = -1;
	while (++i < 3)
	{
		centered_world.xyz_min[i] -= centered_world.center[i];
		centered_world.xyz_max[i] -= centered_world.center[i];
	}
	ml_vector3_copy(centered_world.center, (t_vec3){0, 0, 0});
	return (centered_world);
}

/*
** Sorts all but skybox triangles to be ordered by z depth relative to
** world box (will speed up depth testing and allow transparent rendering)
** render_triangles[0] = normal triangles,
** render_triangles[1] = transparent ones
** offsets render triangles by skybox triangles and reverts back after sort
*/
void			sort_render_triangles_by_depth(t_doom3d *app,
					t_tri_vec **render_triangles,
					int32_t skybox_offset)
{
	t_box3d				centered_world;
	t_bool				is_skybox_offset;

	centered_world = origo_centered_world_box(app);
	is_skybox_offset = app->active_scene->scene_id != scene_id_editor3d;
	if (is_skybox_offset)
	{
		render_triangles[0]->triangles =
			render_triangles[0]->triangles + skybox_offset;
		render_triangles[0]->size =
			render_triangles[0]->size - skybox_offset;
	}
	triangle_sort_by_depth(render_triangles[0], app->thread_pool,
		&centered_world);
	if (is_skybox_offset)
	{
		render_triangles[0]->triangles =
			render_triangles[0]->triangles - skybox_offset;
		render_triangles[0]->size =
			render_triangles[0]->size + skybox_offset;
	}
	if (render_triangles[1]->size > 0)
		triangle_sort_by_depth(render_triangles[1], app->thread_pool,
			&centered_world);
}
