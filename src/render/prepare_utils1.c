/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/13 22:44:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_bool			triangle_inside_viewbox(t_doom3d *app,
					t_triangle *triangle)
{
	t_vec3		player_to_corner[3];
	int32_t		i;
	int32_t		j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 3)
			ml_vector3_sub(triangle->vtc[j]->pos, app->player.pos,
				player_to_corner[j]);
		if (ml_vector3_dot(player_to_corner[0],
				app->active_scene->main_camera->viewplanes[i].normal) < 0 &&
			ml_vector3_dot(player_to_corner[1],
				app->active_scene->main_camera->viewplanes[i].normal) < 0 &&
			ml_vector3_dot(player_to_corner[2],
				app->active_scene->main_camera->viewplanes[i].normal) < 0)
			return (false);
	}
	return (true);
}

t_bool			triangle_too_far(t_doom3d *app, t_triangle *triangle)
{
	float		too_far;
	t_vec3		player_to_corner[3];
	int32_t		i;

	too_far = app->unit_size * 50;
	i = -1;
	while (++i < 3)
		ml_vector3_sub(triangle->vtc[i]->pos, app->player.pos,
			player_to_corner[i]);
	if (ml_vector3_mag(player_to_corner[0]) > too_far &&
		ml_vector3_mag(player_to_corner[1]) > too_far &&
		ml_vector3_mag(player_to_corner[2]) > too_far)
		return (true);
	return (false);
}

/*
** Apply rotation and translation to render triangle
*/

void			prepare_render_triangle(t_doom3d *app,
									t_triangle *r_triangle,
									t_triangle *triangle, t_vertex *vtc)
{
	int32_t		i;

	ft_memcpy(r_triangle, triangle, sizeof(t_triangle));
	i = -1;
	while (++i < 3)
	{
		r_triangle->vtc[i] = &vtc[i];
		ml_vector3_copy(triangle->vtc[i]->pos, r_triangle->vtc[i]->pos);
		ml_matrix4_mul_vec3(app->player.inv_translation,
			r_triangle->vtc[i]->pos, r_triangle->vtc[i]->pos);
		ml_matrix4_mul_vec3(app->player.inv_rotation,
			r_triangle->vtc[i]->pos, r_triangle->vtc[i]->pos);
	}
	l3d_triangle_update(r_triangle);
	triangle->clipped = false;
}

/*
** Skybox is rotated, but it is not translated unlike other objects in scene
*/

void			prepare_skybox_render_triangle(t_doom3d *app,
									t_triangle *r_triangle,
									t_triangle *triangle, t_vertex *vtc)
{
	int32_t		i;

	ft_memcpy(r_triangle, triangle, sizeof(t_triangle));
	i = -1;
	while (++i < 3)
	{
		r_triangle->vtc[i] = &vtc[i];
		ml_vector3_copy(triangle->vtc[i]->pos, r_triangle->vtc[i]->pos);
		ml_matrix4_mul_vec3(app->player.inv_rotation,
			r_triangle->vtc[i]->pos, r_triangle->vtc[i]->pos);
	}
	l3d_triangle_update(r_triangle);
	r_triangle->clipped = false;
}

/*
** If any corner of aabb (axis aligned bounding box) is inside the viewbox
** the object should be considered to be inside viewbox.
*/

t_bool			object_inside_viewbox(t_doom3d *app, t_3d_object *obj)
{
	int32_t	i;
	int32_t	j;
	t_vec3	origin_to_corner[8];
	t_vec3	add;
	t_vec3	origin;

	ml_vector3_mul(app->player.forward, NEAR_CLIP_DIST, add);
	ml_vector3_add(app->player.pos, add, origin);
	set_aabb_origin_to_corners(obj, origin, origin_to_corner);
	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 8)
			if (ml_vector3_dot(origin_to_corner[0],
				app->active_scene->main_camera->viewplanes[i].normal) >= 0)
				return (true);
	}
	return (false);
}
