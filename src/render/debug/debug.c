/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:07:34 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 20:38:17 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	triangle_wireframe_draw(t_sub_framebuffer *buffers,
					t_vec2 points2d[3], uint32_t color)
{
	l3d_line_draw(buffers->buffer, (unsigned int [2]){
		buffers->width, buffers->height
	}, (int [2][2]){{points2d[0][0] + buffers->x_offset,
		points2d[0][1] + buffers->y_offset},
	{points2d[1][0] + buffers->x_offset,
		points2d[1][1] + buffers->y_offset}}, color);
	l3d_line_draw(buffers->buffer, (unsigned int [2]){
		buffers->width, buffers->height
	}, (int [2][2]){{points2d[1][0] + buffers->x_offset,
		points2d[1][1] + buffers->y_offset},
	{points2d[2][0] + buffers->x_offset,
		points2d[2][1] + buffers->y_offset}}, color);
	l3d_line_draw(buffers->buffer, (unsigned int [2]){
		buffers->width, buffers->height
	}, (int [2][2]){{points2d[2][0] + buffers->x_offset,
		points2d[2][1] + buffers->y_offset},
	{points2d[0][0] + buffers->x_offset,
		points2d[0][1] + buffers->y_offset}}, color);
}

void	draw_selected_wireframe(t_render_work *work)
{
	t_sub_framebuffer	*sub_buffer;
	t_triangle			*triangle;
	int32_t				i;
	uint32_t			color;

	sub_buffer = work->framebuffer->sub_buffers[work->sub_buffer_i];
	i = -1;
	while (++i < (int32_t)work->render_triangles->size)
	{
		triangle = work->render_triangles->triangles[i];
		color = 0x00ff00ff;
		if (triangle->material->shading_opts & e_shading_green)
			color = 0x0000ffff;
		if (!(triangle->material->shading_opts & e_shading_select)
			|| triangle->clipped
			|| triangle_outside_frame(triangle, sub_buffer))
			continue ;
		triangle_wireframe_draw(sub_buffer, triangle->points_2d, color);
	}
}

void	draw_selected_enemies_direction(t_render_work *work)
{
	int32_t		i;
	t_3d_object	*obj;

	i = -1;
	while (++i < work->app->editor.num_selected_objects)
	{
		obj = work->app->editor.selected_objects[i];
		if (obj->type == object_type_npc)
			draw_enemy_direction(work->app,
				work->framebuffer->sub_buffers[work->sub_buffer_i],
				obj);
	}
}

void	draw_npc_dirs(t_render_work *work)
{
	int32_t		i;
	t_3d_object	*obj;

	i = -1;
	while (++i < (int32_t)(work->app->active_scene->num_objects
		+ work->app->active_scene->num_deleted))
	{
		obj = work->app->active_scene->objects[i];
		if (obj && obj->type == object_type_npc)
			draw_enemy_direction(work->app,
				work->framebuffer->sub_buffers[work->sub_buffer_i], obj);
	}
}

void	draw_editor_placement_position(t_render_work *work)
{
	t_vec3		place_pos;
	t_doom3d	*app;
	t_vec3		edge1[2];
	t_vec3		edge2[2];
	t_vec3		edge3[2];

	app = work->app;
	editor_pos_camera_front(app, place_pos);
	ml_vector3_add(place_pos, (t_vec3){0, 0, app->unit_size * 0.3}, edge1[0]);
	ml_vector3_sub(place_pos, (t_vec3){0, 0, app->unit_size * 0.3}, edge1[1]);
	ml_vector3_add(place_pos, (t_vec3){app->unit_size * 0.3, 0, 0}, edge2[0]);
	ml_vector3_sub(place_pos, (t_vec3){app->unit_size * 0.3, 0, 0}, edge2[1]);
	ml_vector3_add(place_pos, (t_vec3){0, app->unit_size * 0.3, 0}, edge3[0]);
	ml_vector3_sub(place_pos, (t_vec3){0, app->unit_size * 0.3, 0}, edge3[1]);
	draw_debug_line(app, work->framebuffer->sub_buffers[work->sub_buffer_i],
		(t_vec3[2]){{edge1[0][0], edge1[0][1], edge1[0][2]},
	{edge1[1][0], edge1[1][1], edge1[1][2]}}, 0x00ffffff);
	draw_debug_line(app, work->framebuffer->sub_buffers[work->sub_buffer_i],
		(t_vec3[2]){{edge2[0][0], edge2[0][1], edge2[0][2]},
	{edge2[1][0], edge2[1][1], edge2[1][2]}}, 0x00ffffff);
	draw_debug_line(app, work->framebuffer->sub_buffers[work->sub_buffer_i],
		(t_vec3[2]){{edge3[0][0], edge3[0][1], edge3[0][2]},
	{edge3[1][0], edge3[1][1], edge3[1][2]}}, 0x00ffffff);
}
