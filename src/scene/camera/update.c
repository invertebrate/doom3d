/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:00:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 12:38:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Update camera with position, its forward, up and sideways vectors, dimensions
** and focal length (affects field of view)
*/

void	update_camera(t_camera *camera, float dims_focal_length[3],
					t_vec3 forward_up_sideways[3], t_vec3 pos)
{
	float		dims[2];

	dims[0] = dims_focal_length[0];
	dims[1] = dims_focal_length[1];
	camera->near_clip = Z_DIR * NEAR_CLIP_DIST;
	camera->far_clip = Z_DIR * FAR_CLIP_DIST;
	ml_vector3_set(camera->screen.origin, 0, 0, dims_focal_length[2]);
	ml_vector3_set(camera->screen.normal, 0, 0, -Z_DIR);
	ml_vector3_copy(pos, camera->world_pos);
	set_camera_viewbox(camera, dims, forward_up_sideways);
}

void	update_player_camera(t_doom3d *app)
{
	t_vec3	forward_up_sideways[3];
	float	dims[2];
	float	focal_length;

	dims[0] = app->window->framebuffer->width / 2.0;
	dims[1] = app->window->framebuffer->height / 2.0;
	focal_length = Z_DIR * app->window->framebuffer->width * 0.65;
	ml_vector3_copy(app->player.forward, forward_up_sideways[0]);
	ml_vector3_copy(forward_up_sideways[0],
		app->active_scene->main_camera->forward);
	ml_vector3_copy(app->player.up, forward_up_sideways[1]);
	ml_vector3_copy(app->player.sideways, forward_up_sideways[2]);
	ml_matrix4_copy(app->player.rotation,
		app->active_scene->main_camera->rotation);
	ml_matrix4_copy(app->player.inv_rotation,
		app->active_scene->main_camera->inv_rotation);
	ml_matrix4_copy(app->player.translation,
		app->active_scene->main_camera->translation);
	ml_matrix4_copy(app->player.inv_translation,
		app->active_scene->main_camera->inv_translation);
	update_camera(app->active_scene->main_camera,
		(float [3]){dims[0], dims[1], focal_length},
		forward_up_sideways, app->player.pos);
}

static void	update_third_person_camera_by_pos(t_doom3d *app, t_vec3 pos)
{
	t_vec3	forward_up_sideways[3];
	float	dims[2];
	float	focal_length;

	ft_memset(forward_up_sideways, 0, sizeof(t_vec3) * 3);
	dims[0] = app->window->framebuffer->width / 2.0;
	dims[1] = app->window->framebuffer->height / 2.0;
	focal_length = Z_DIR * app->window->framebuffer->width * 0.65;
	ml_vector3_copy(app->player.forward, forward_up_sideways[0]);
	ml_vector3_copy(forward_up_sideways[0],
		app->active_scene->third_person_camera->forward);
	ml_vector3_copy(app->player.up, forward_up_sideways[1]);
	ml_vector3_copy(app->player.sideways, forward_up_sideways[2]);
	ml_matrix4_copy(app->player.rotation,
		app->active_scene->third_person_camera->rotation);
	ml_matrix4_copy(app->player.inv_rotation,
		app->active_scene->third_person_camera->inv_rotation);
	ml_matrix4_translation(pos[0], pos[1], pos[2],
		app->active_scene->third_person_camera->translation);
	ml_matrix4_translation(-pos[0], -pos[1], -pos[2],
		app->active_scene->third_person_camera->inv_translation);
	update_camera(app->active_scene->third_person_camera,
		(float [3]){dims[0], dims[1], focal_length},
		forward_up_sideways, pos);
}

/*
** For third person camera update:
** To prevent going outside walls, we clamp distance by hit->t
*/

static float	clamp_distance_by_surroundings(t_doom3d *app, t_vec3 dir,
					float dist)
{
	t_hits	*hits;
	t_hit	*closest_triangle_hit;
	t_vec3	origin;
	t_vec3	add;

	if (!app->active_scene->triangle_tree)
		return (dist);
	hits = NULL;
	ml_vector3_mul(dir, app->player.aabb.size[0] / 2.0, add);
	ml_vector3_add(app->player.pos, add, origin);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
			dir, &hits))
	{
		l3d_get_closest_facing_triangle_hit(hits, &closest_triangle_hit,
			dir, -1);
		if (closest_triangle_hit != NULL)
			dist = fmin(closest_triangle_hit->t + 0.1 * app->unit_size, dist);
		l3d_delete_hits(&hits);
	}
	return (dist);
}

/*
** Initialize camera to be behind player. This is only called in 3d rendered
** scenes and app->settings.is_third_person should always be false initially
*/

void	update_third_person_camera(t_doom3d *app)
{
	t_vec3	new_pos;
	t_vec3	add;
	t_vec3	dir;
	float	dist;

	dist = app->active_scene->third_person_camera_distance;
	ml_vector3_mul(app->player.forward, -1, dir);
	dist = clamp_distance_by_surroundings(app, dir, dist);
	ml_vector3_mul(dir, dist, add);
	ml_vector3_add(app->player.pos, add, new_pos);
	update_third_person_camera_by_pos(app, new_pos);
}
