/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:07:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/30 18:31:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	same_signs(float a, float b)
{
	return (a != 0 && b != 0 && a * b >= 0);
}

static int32_t	lines_intersect(t_vec2 edge1[2], t_vec2 edge2[2], t_vec2 intersect)
{
	float	coefs[6];
	float	signs[4];
	float	denom;
	float	offset;
	float	num;

	coefs[0] = edge1[1][1] - edge1[0][1];
	coefs[2] = edge1[0][0] - edge1[1][0];
	coefs[4] = edge1[1][0] * edge1[0][1] - edge1[0][0] * edge1[1][1];
	signs[2] = coefs[0] * edge2[0][0] + coefs[2] * edge2[0][1] + coefs[4];
	signs[3] = coefs[0] * edge2[1][0] + coefs[2] * edge2[1][1] + coefs[4];
	if (same_signs( signs[2], signs[3] ))
		return (0);
	coefs[1] = edge2[1][1] - edge2[0][1];
	coefs[3] = edge2[0][0] - edge2[1][0];
	coefs[5] = edge2[1][0] * edge2[0][1] - edge2[0][0] * edge2[1][1];
	signs[0] = coefs[1] * edge1[0][0] + coefs[3] * edge1[0][1] + coefs[5];
	signs[1] = coefs[1] * edge1[1][0] + coefs[3] * edge1[1][1] + coefs[5];
	if (same_signs( signs[0], signs[1] ))
		return (0);
	denom = coefs[0] * coefs[3] - coefs[1] * coefs[2];
	if (denom == 0)
		return (2);
	offset = denom < 0 ? - denom / 2 : denom / 2;
	num = coefs[2] * coefs[5] - coefs[3] * coefs[4];
	intersect[0] = ( num < 0 ? num - offset : num + offset ) / denom;
	num = coefs[1] * coefs[4] - coefs[0] * coefs[5];
	intersect[1] = ( num < 0 ? num - offset : num + offset ) / denom;
	return (1);
}

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

static void		find_buffer_intersections(t_sub_framebuffer *buffer,
					t_vec3 points[2], int32_t is_intersect[4],
					t_vec2 intersects[4])
{
	is_intersect[0] = lines_intersect((t_vec2[2]){{points[0][0],points[0][1]},
		{points[1][0], points[1][1]}}, (t_vec2[2]){{0, 0}, {0, buffer->height}},
		intersects[0]);
	is_intersect[1] = lines_intersect((t_vec2[2]){{points[0][0],points[0][1]},
		{points[1][0], points[1][1]}}, (t_vec2[2]){{0, 0}, {buffer->width, 0}},
		intersects[1]);
	is_intersect[2] = lines_intersect((t_vec2[2]){{points[0][0],points[0][1]},
		{points[1][0], points[1][1]}}, (t_vec2[2]){{buffer->width, 0},
			{buffer->width, buffer->height}}, intersects[2]);
	is_intersect[3] = lines_intersect((t_vec2[2]){{points[0][0],points[0][1]},
		{points[1][0], points[1][1]}}, (t_vec2[2]){{0, buffer->height},
			{buffer->width, buffer->height}}, intersects[3]);
}

static t_bool	point2d_is_inside_aabb(t_vec2 point,
					t_vec2 xymin, t_vec2 xymax)
{
	return (point[0] >= xymin[0] && point[0] < xymax[0] &&
		point[1] >= xymin[1] && point[1] < xymax[1]);
}

static t_bool	should_draw_line_modify_points(t_sub_framebuffer *buffer,
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
		i = 0;
		while (is_intersect[i] != 1)
			i++;
		ml_vector2_copy(intersects[i++], points[0]);
		while (is_intersect[i] != 1)
			i++;
		ml_vector2_copy(intersects[i], points[1]);
		return (true);
	}
	else if (count == 1)
	{
		i = 0;
		while (is_intersect[i] != 1)
			i++;
		if (point2d_is_inside_aabb(points[0],
			(t_vec2){0, 0}, (t_vec2){buffer->width, buffer->height}))
			ml_vector2_copy(intersects[i], points[1]);
		else
			ml_vector2_copy(intersects[i], points[0]);
		return (true);
	}
	return (point2d_is_inside_aabb(points[0],
			(t_vec2){0, 0}, (t_vec2){buffer->width, buffer->height}) &&
			point2d_is_inside_aabb(points[1],
			(t_vec2){0, 0}, (t_vec2){buffer->width, buffer->height}));
}

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
	clip_3d_line(app, points);
	ml_vector2_add(points[0], (t_vec2){buffer->x_offset, buffer->y_offset},
		points[0]);
	ml_vector2_add(points[1], (t_vec2){buffer->x_offset, buffer->y_offset},
		points[1]);
	find_buffer_intersections(buffer, points, is_intersect, intersects);
	if (should_draw_line_modify_points(buffer, points,
		is_intersect, intersects))
		l3d_line_draw(buffer->buffer, (uint32_t[2]){
			buffer->width, buffer->height},
			(int32_t[2][2]){{points[0][0],points[0][1]},
			{points[1][0], points[1][1]}}, color);
}

void			draw_editor_debug_grid(t_render_work *work)
{
	t_sub_framebuffer	*sub_buffer;
	int32_t				i;
	t_vec3				points[2];
	float				length;
	uint32_t			line_color;

	sub_buffer = work->framebuffer->sub_buffers[work->sub_buffer_i];
	length = 100;
	line_color = 0x202020ff;
	i = -length / 2 - 1;
	while (++i <= length / 2)
	{
		ml_vector3_copy((t_vec3){i * work->app->unit_size, 0,
			(-length / 2.0) * work->app->unit_size}, points[0]);
		ml_vector3_copy((t_vec3){i * work->app->unit_size, 0,
			(length / 2.0) * work->app->unit_size}, points[1]);
		draw_debug_line(work->app, sub_buffer, points, line_color);
		ml_vector3_copy((t_vec3){(-length / 2.0) * work->app->unit_size, 0,
			i * work->app->unit_size}, points[0]);
		ml_vector3_copy((t_vec3){(length / 2.0) * work->app->unit_size, 0,
			i * work->app->unit_size}, points[1]);
		draw_debug_line(work->app, sub_buffer, points, line_color);
	}
}
