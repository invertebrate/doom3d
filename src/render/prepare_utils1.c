/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/08 20:24:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_bool	triangle_inside_viewbox(t_camera *camera,
					t_triangle *triangle)
{
	t_vec3		p_to_c[3];
	int32_t		ij[2];
	t_bool		is_outside;
	t_vec3		add;
	t_vec3		origin;

	ml_vector3_mul(camera->forward, -NEAR_CLIP_DIST, add);
	ml_vector3_add(camera->world_pos, add, origin);
	ij[0] = -1;
	while (++ij[0] < 5)
	{
		is_outside = true;
		ij[1] = -1;
		while (++ij[1] < 3)
		{
			ml_vector3_sub(origin, triangle->vtc[ij[1]]->pos, p_to_c[ij[1]]);
			if (ml_vector3_dot(p_to_c[ij[1]],
					camera->viewplanes[ij[0]].normal) < 0 && is_outside)
				is_outside = false;
		}
		if (is_outside)
			return (false);
	}
	return (true);
}

t_bool	triangle_too_far(t_doom3d *app, t_triangle *triangle)
{
	float		too_far;
	t_vec3		player_to_corner[3];
	int32_t		i;
	t_box3d		aabb;
	t_vec3		player_to_center;

	if (triangle->parent->material->shading_opts & e_shading_dont_cull)
		return (false);
	too_far = app->unit_size * EDITOR_VIEW_DIST_UNITS;
	if (app->active_scene->scene_id == scene_id_main_game)
		too_far = app->unit_size * GAME_VIEW_DIST_UNITS;
	i = -1;
	while (++i < 3)
		ml_vector3_sub(triangle->vtc[i]->pos, app->player.pos,
			player_to_corner[i]);
	if (ml_vector3_mag(player_to_corner[0]) > too_far
		&& ml_vector3_mag(player_to_corner[1]) > too_far
		&& ml_vector3_mag(player_to_corner[2]) > too_far)
	{
		aabb = l3d_triangle_bounding_box(triangle);
		if (ml_vector3_mag(player_to_center) <= ml_vector3_mag(aabb.size))
			return (false);
		return (true);
	}
	return (false);
}

/*
** Apply rotation and translation to render triangle
*/

void	prepare_render_triangle(t_doom3d *app,
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
		transform_position_for_rendering(app, r_triangle->vtc[i]->pos);
	}
	l3d_triangle_update(r_triangle);
	triangle->clipped = false;
}

/*
** Skybox is rotated, but it is not translated unlike other objects in scene
*/

void	prepare_skybox_render_triangle(t_doom3d *app,
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

t_bool	object_inside_viewbox(t_camera *camera, t_3d_object *obj)
{
	int32_t		ij[2];
	t_vec3		origin_to_corner[8];
	t_bool		is_outside;
	t_vec3		add;
	t_vec3		origin;

	ml_vector3_mul(camera->screen.normal, -NEAR_CLIP_DIST, add);
	ml_vector3_add(camera->world_pos, add, origin);
	set_aabb_origin_to_corners(obj, origin, origin_to_corner);
	ij[0] = -1;
	while (++ij[0] < 5)
	{
		is_outside = true;
		ij[1] = -1;
		while (++ij[1] < 8)
			if (ml_vector3_dot(origin_to_corner[ij[1]],
					camera->viewplanes[ij[0]].normal) < 0
				&& is_outside)
				is_outside = false;
		if (is_outside)
			return (false);
	}
	return (true);
}
