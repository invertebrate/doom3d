/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_object_by_mouse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 01:25:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/06 13:22:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Transform mouse x & mouse y on window between 0.0 - 1.0 inside
** editor view.
*/

static void	get_mouse_editor_scale(t_doom3d *app, t_vec2 mouse_editor_pos)
{
	t_vec2	mouse_pos;

	ml_vector2_copy((t_vec2){app->mouse.x, app->mouse.y}, mouse_pos);
	ml_vector2_sub(mouse_pos, app->window->view_3d_pos, mouse_pos);
	ml_vector2_copy((t_vec2){
		(mouse_pos[0] / app->window->framebuffer->width),
		(mouse_pos[1] / app->window->framebuffer->height)}, mouse_pos);
	ml_vector2_copy((t_vec2){
		((float)app->window->framebuffer->width
			/ (float)app->window->framebuffer_3d->width)
		* mouse_pos[0],
		((float)app->window->framebuffer->height
			/ (float)app->window->framebuffer_3d->height)
		* mouse_pos[1]}, mouse_editor_pos);
}

static void	multiply_by_mouse_editor_scale(t_doom3d *app, t_vec3 add,
					t_vec3 mouse_world_pos)
{
	t_vec2	mouse_editor_scale;

	get_mouse_editor_scale(app, mouse_editor_scale);
	ml_vector3_mul(app->player.sideways,
		app->window->framebuffer_3d->width, add);
	ml_vector3_mul(add, mouse_editor_scale[0], add);
	ml_vector3_add(mouse_world_pos, add, mouse_world_pos);
	ml_vector3_mul(app->player.up,
		-app->window->framebuffer_3d->height, add);
	ml_vector3_mul(add, mouse_editor_scale[1], add);
	ml_vector3_add(mouse_world_pos, add, mouse_world_pos);
}

/*
** 1. Go to screen origin
** 2. Use vectors to get to left top corner
** 3. Multiply sideways & down vectors by mouse editor scale
** 4. Got it!
*/

void	get_mouse_world_position(t_doom3d *app, t_vec3 mouse_world_pos)
{
	t_vec3	screen_origin;
	t_vec3	add;
	t_vec3	dirs[4];
	float	dims[2];

	dims[0] = app->window->framebuffer_3d->width / 2.0;
	dims[1] = app->window->framebuffer_3d->height / 2.0;
	ml_vector3_mul(app->player.forward,
		ml_vector3_mag(app->active_scene->main_camera->screen.origin), add);
	ml_vector3_add(app->player.pos, add, screen_origin);
	ml_vector3_mul(app->player.up, dims[1], dirs[0]);
	ml_vector3_mul(app->player.sideways, dims[0], dirs[1]);
	ml_vector3_mul(app->player.up, -dims[1], dirs[2]);
	ml_vector3_mul(app->player.sideways, -dims[0], dirs[3]);
	ml_vector3_add(screen_origin, dirs[3], mouse_world_pos);
	ml_vector3_add(mouse_world_pos, dirs[0], mouse_world_pos);
	multiply_by_mouse_editor_scale(app, add, mouse_world_pos);
}

/*
** Return object selected by mouse (via raycasting)
*/

t_3d_object	*editor_object_by_mouse(t_doom3d *app)
{
	t_vec3			mouse_world_pos;
	t_vec3			dir;
	t_hits			*hits;
	t_hit			*closest_triangle_hit;
	t_3d_object		*hit_obj;

	hits = NULL;
	hit_obj = NULL;
	get_mouse_world_position(app, mouse_world_pos);
	ml_vector3_sub(mouse_world_pos, app->player.pos, dir);
	ml_vector3_normalize(dir, dir);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.pos,
			dir, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_triangle_hit, -1);
		if (closest_triangle_hit != NULL)
		{
			hit_obj = closest_triangle_hit->triangle->parent;
		}
		l3d_delete_hits(&hits);
	}
	return (hit_obj);
}
