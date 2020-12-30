/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:38:59 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/30 22:49:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"


static void		find_aabb_intersections(t_vec2 aabb[2],
					t_vec3 points[2], int32_t is_intersect[4],
					t_vec2 intersects[4])
{
	is_intersect[0] = l3d_2d_lines_intersect(
		(t_vec2[2]){{points[0][0], points[0][1]},
		{points[1][0], points[1][1]}},
			(t_vec2[2]){{aabb[0][0], aabb[0][0]}, {aabb[0][0], aabb[1][1]}},
		intersects[0]);
	is_intersect[1] = l3d_2d_lines_intersect(
		(t_vec2[2]){{points[0][0], points[0][1]},
		{points[1][0], points[1][1]}},
		(t_vec2[2]){{aabb[0][0], aabb[0][0]}, {aabb[1][0], aabb[0][1]}},
		intersects[1]);
	is_intersect[2] = l3d_2d_lines_intersect(
		(t_vec2[2]){{points[0][0], points[0][1]},
		{points[1][0], points[1][1]}},
		(t_vec2[2]){{aabb[1][0], aabb[0][0]}, {aabb[1][0], aabb[1][1]}},
		intersects[2]);
	is_intersect[3] = l3d_2d_lines_intersect(
		(t_vec2[2]){{points[0][0], points[0][1]},
		{points[1][0], points[1][1]}},
		(t_vec2[2]){{aabb[0][0], aabb[1][1]}, {aabb[1][0], aabb[1][1]}},
		intersects[3]);
}

static void		clip_3d_line_and_screen_intersect(t_doom3d *app, t_vec3 points[2])
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

static void		copy_two_intersections(int32_t is_intersect[4],
					t_vec2 intersects[4], t_vec3 points[2])
{
	int32_t		i;

	i = 0;
	while (is_intersect[i] != 1)
		i++;
	ml_vector2_copy(intersects[i++], points[0]);
	while (is_intersect[i] != 1)
		i++;
	ml_vector2_copy(intersects[i], points[1]);
}

static void		copy_one_intersections(t_vec2 aabb[2],
					int32_t is_intersect[4], t_vec2 intersects[4],
					t_vec3 points[2])
{
	int32_t		i;

	i = 0;
	while (is_intersect[i] != 1)
		i++;
	if (l3d_point2d_inside_aabb(points[0], aabb))
		ml_vector2_copy(intersects[i], points[1]);
	else
		ml_vector2_copy(intersects[i], points[0]);
}

/*
** If line intersects sub buffer twice, modify point1 and point2 to be
** those intersections. Draw.
** If line intersects once, check which point is inside sub buffer. Modify
** the other. Draw.
** If line intersects none, check if both points are inside, draw.
** Else don't draw.
*/

static t_bool	should_draw_line_modify_points(t_vec2 aabb[2],
					t_vec3 points[2], int32_t is_intersect[4],
					t_vec2 intersects[4])
{
	int32_t		i;
	int32_t		count;

	i = -1;
	count = 0;
	while (++i < 4)
		if (is_intersect[i] == 1)
			count++;
	if (count == 2)
	{
		copy_two_intersections(is_intersect, intersects, points);
		return (true);
	}
	else if (count == 1)
	{
		copy_one_intersections(aabb, is_intersect, intersects, points);
		return (true);
	}
	return (l3d_point2d_inside_aabb(points[0], aabb) &&
			l3d_point2d_inside_aabb(points[1], aabb));
}

/*
** Based on given sub buffer limitations (screen is split to sub buffers)
** renders a 2d line from 3d points.
** 1. Transform 3d points to world origin 0, 0, 0
** 2. Clip 3d lines with near plane and return screen intersection = 2d lines
** 3. Offset 2d lines by sub buffers offset
** 4. Cut lines to only segment inside sub buffer (mandatory for performance)
** 5. Draw 2d line
*/

void			draw_debug_line(t_doom3d *app,
					t_sub_framebuffer *buffer, t_vec3 points[2],
					uint32_t color)
{
	int32_t		i;
	t_vec2		intersects[4];
	int32_t		is_intersect[4];

	i = -1;
	while (++i < 2)
	{
		ml_matrix4_mul_vec3(app->player.inv_translation,
			points[i], points[i]);
		ml_matrix4_mul_vec3(app->player.inv_rotation,
			points[i], points[i]);
	}
	clip_3d_line_and_screen_intersect(app, points);
	ml_vector2_add(points[0], (t_vec2){buffer->x_offset, buffer->y_offset},
		points[0]);
	ml_vector2_add(points[1], (t_vec2){buffer->x_offset, buffer->y_offset},
		points[1]);
	find_aabb_intersections((t_vec2[2]){{0, 0},
		{buffer->width, buffer->height}}, points, is_intersect, intersects);
	if (should_draw_line_modify_points((t_vec2[2]){{0, 0},
		{buffer->width, buffer->height}}, points, is_intersect, intersects))
		l3d_line_draw(buffer->buffer, (uint32_t[2]){
			buffer->width, buffer->height},
			(int32_t[2][2]){{points[0][0],points[0][1]},
			{points[1][0], points[1][1]}}, color);
}
