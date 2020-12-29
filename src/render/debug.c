/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:07:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/29 21:24:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

// static t_bool	ray2d_intersect_aabb(float minxy[2], float maxxy[2],
// 					t_vec2 org_dir[2], float *dist)
// {
// 	float	t[6];
// 	float	inv_dirx;
// 	float	inv_diry;

// 	inv_dirx = 1.0f / org_dir[1][0];
// 	inv_diry = 1.0f / org_dir[1][1];
// 	t[0] = (minxy[0] - org_dir[0][0]) * inv_dirx;
// 	t[1] = (maxxy[0] - org_dir[0][0]) * inv_dirx;
// 	t[2] = (minxy[1] - org_dir[0][1]) * inv_diry;
// 	t[3] = (maxxy[1] - org_dir[0][1]) * inv_diry;
// 	t[4] = l3d_fmax(l3d_fmin(t[0], t[1]), l3d_fmin(t[2], t[3]));
// 	t[5] = l3d_fmin(l3d_fmax(t[0], t[1]), l3d_fmax(t[2], t[3]));
// 	if (t[4] < 0 || t[4] > t[5])
// 		return (false);
// 	*dist = t[4];
// 	return (true);
// }

static void		clip_3d_line(t_doom3d *app, t_vec3 points[2])
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

void			draw_debug_line(t_doom3d *app,
					t_sub_framebuffer *buffer, t_vec3 points[2],
					uint32_t color)
{
	int32_t		i;
	// t_vec2		dir;
	// t_vec2		add;
	// float		t;

	i = -1;
	while (++i < 2)
	{
		ml_matrix4_mul_vec3(app->player.inv_translation,
			points[i], points[i]);
		ml_matrix4_mul_vec3(app->player.inv_rotation,
			points[i], points[i]);
	}
	clip_3d_line(app, points);
	ml_vector3_add(points[0], (t_vec3){buffer->x_offset, buffer->y_offset, 0},
		points[0]);
	ml_vector3_add(points[1], (t_vec3){buffer->x_offset, buffer->y_offset, 0},
		points[1]);
	l3d_line_draw(buffer->buffer, (uint32_t[2]){
		buffer->width, buffer->height},
		(int32_t[2][2]){{points[0][0],points[0][1]},
		{points[1][0], points[1][1]}}, color);
}
