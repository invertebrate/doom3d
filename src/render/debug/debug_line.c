/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:38:59 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/30 23:08:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		clip_3d_line_and_screen_intersect(t_doom3d *app,
					t_vec3 points[2])
{
	t_vec3		near_to_point;
	t_plane		near;
	t_vec3		dir;
	t_ray		ray;
	int32_t		i;

	ml_vector3_sub(points[1], points[0], dir);
	ml_vector3_copy((t_vec3){0, 0, NEAR_CLIP_DIST}, near.origin);
	ml_vector3_copy((t_vec3){0, 0, Z_DIR}, near.normal);
	near.d = NEAR_CLIP_DIST;
	i = -1;
	while (++i < 2)
	{
		ml_vector3_sub(near.origin, points[i], near_to_point);
		if (ml_vector3_dot(near.normal, near_to_point) >= 0)
		{
			l3d_ray_set(dir, points[i], &ray);
			l3d_plane_ray_hit(&near, &ray, points[i]);
		}
		l3d_ray_set(points[i], (t_vec3){0, 0, 0}, &ray);
		l3d_plane_ray_hit(&app->active_scene->main_camera->screen,
			&ray, points[i]);
	}
}

/*
** Based on given sub buffer limitations (screen is split to sub buffers)
** renders a 2d line from 3d points.
** 1. Transform 3d points to world origin 0, 0, 0
** 2. Clip 3d lines with near plane and return screen intersection = 2d lines
** 3. Offset 2d lines by sub buffers offset
** 4. Draw 2d line
*/

void			draw_debug_line(t_doom3d *app,
					t_sub_framebuffer *buffer, t_vec3 edge[2],
					uint32_t color)
{
	int32_t		i;

	i = -1;
	while (++i < 2)
	{
		ml_matrix4_mul_vec3(app->player.inv_translation,
			edge[i], edge[i]);
		ml_matrix4_mul_vec3(app->player.inv_rotation,
			edge[i], edge[i]);
	}
	clip_3d_line_and_screen_intersect(app, edge);
	ml_vector2_add(edge[0], (t_vec2){buffer->x_offset, buffer->y_offset},
		edge[0]);
	ml_vector2_add(edge[1], (t_vec2){buffer->x_offset, buffer->y_offset},
		edge[1]);
	l3d_line_draw(buffer->buffer, (uint32_t[2]){
		buffer->width, buffer->height},
		(int32_t[2][2]){{edge[0][0],edge[0][1]},
		{edge[1][0], edge[1][1]}}, color);
}
