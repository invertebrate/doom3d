/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 23:58:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Prepares triangles for parallel rendering.
** but ignore skybox.
** Sort triangles in z order curve inside world box to speed up render &
** allow transparent render in proper order
*/
t_tri_vec		**prepare_render_triangles(t_doom3d *app)
{
	t_tri_vec			**render_triangles;
	uint32_t			initial_transp_cap;
	int32_t				skybox_offset;

	reset_render_triangle_pool(app);
	initial_transp_cap = 512;
	error_check(!(render_triangles = ft_calloc(sizeof(*render_triangles) * 2)),
		"Failed to allocate render triangle vector pointers");
	render_triangles[0] =
		l3d_triangle_vec_with_capacity(app->active_scene->num_triangles + 12);
	render_triangles[1] =
		l3d_triangle_vec_with_capacity(initial_transp_cap);
	if (app->active_scene->scene_id != scene_id_editor3d)
		add_skybox_render_triangles(app, render_triangles);
	skybox_offset = render_triangles[0]->size;
	add_objects_render_triangles(app, render_triangles);
	add_temp_object_render_triangles(app, render_triangles);
	sort_render_triangles_by_depth(app, render_triangles, skybox_offset);
	return (render_triangles);
}
