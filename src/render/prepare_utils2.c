/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 19:45:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		calculate_2d_points(t_vec2 *points_2d, t_vec3 *hits)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		points_2d[i][0] = hits[i][0];
		points_2d[i][1] = hits[i][1];
	}
}

static t_bool	triangle_behind_camera(t_triangle *triangle, t_camera *camera)
{
	if (triangle->vtc[0]->pos[2] < camera->near_clip &&
		triangle->vtc[1]->pos[2] < camera->near_clip &&
		triangle->vtc[2]->pos[2] < camera->near_clip)
		return (true);
	return (false);
}

static t_bool	is_triangle_facing(t_triangle *triangle, t_vec3 dir)
{
	return (ml_vector3_dot(triangle->normal, dir) < 0);
}

t_bool			is_rendered(t_doom3d *app, t_triangle *triangle)
{
	t_vec3 dir;

	if (triangle_behind_camera(triangle, app->active_scene->main_camera))
		return (false);
	ml_vector3_sub(triangle->center,
		app->active_scene->main_camera->origin, dir);
	if (app->active_scene->scene_id != scene_id_editor3d &&
		!is_triangle_facing(triangle, dir))
		return (false);
	return (true);
}

t_bool			screen_intersection(t_doom3d *app, t_triangle *triangle)
{
	t_ray		rays[3];
	t_vec3		hits[3];
	int			k;

	k = -1;
	while (++k < 3)
	{
		ml_vector3_set(hits[k], 0.0, 0.0, 0.0);
		l3d_ray_set(triangle->vtc[k]->pos, (t_vec3){0, 0, 0}, &rays[k]);
		if (!(l3d_plane_ray_hit(&app->active_scene->main_camera->screen,
			&rays[k], hits[k])))
		{
			LOG_WARN("Screen intersection from degenerate triangles");
			ml_vector3_set_all(hits[k], 0);
		}
	}
	calculate_2d_points(triangle->points_2d, hits);
	return (true);
}
