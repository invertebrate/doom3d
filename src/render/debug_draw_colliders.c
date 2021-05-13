/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_draw_colliders.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:44:41 by veilo             #+#    #+#             */
/*   Updated: 2021/05/13 18:52:18 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	draw_sphere_collider(t_render_work *work)
{
	int		i;
	t_vec3	points[2];
	t_vec3	end_point;
	t_vec3	dir;

	i = -1;
	while (++i < COLLIDER_RAY_TOTAL)
	{
		ml_vector3_copy(work->app->player.collider.rays[i].dir, dir);
		ml_vector3_mul(dir, work->app->player.collider.sphere.radius, dir);
		ml_vector3_add(work->app->player.collider.sphere.pos, dir, end_point);
		ml_vector3_copy(work->app->player.collider.sphere.pos, points[0]);
		ml_vector3_copy(end_point, points[1]);
		draw_debug_line(work->app,
			work->framebuffer->sub_buffers[work->sub_buffer_i],
			points, 0xffffffff);
	}
}

void	draw_cylinder_collider(t_render_work *work)
{
	int		i;
	t_vec3	points[2];
	t_vec3	end_point;
	t_vec3	dir;

	i = -1;
	while (++i < COLLIDER_RAY_TOTAL)
	{
		ml_vector3_copy(work->app->player.collider_ground.rays[i].dir, dir);
		ml_vector3_mul(dir, work->app->player.collider_ground.cylinder.height,
			dir);
		ml_vector3_add(dir, work->app->player.collider_ground.rays[i].origin,
			dir);
		ml_vector3_copy(dir, end_point);
		ml_vector3_copy(work->app->player.collider_ground.rays[i].origin,
			points[0]);
		ml_vector3_copy(end_point, points[1]);
		draw_debug_line(work->app,
			work->framebuffer->sub_buffers[work->sub_buffer_i],
			points, 0xfff00fff);
	}
}
