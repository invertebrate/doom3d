/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:00:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 19:13:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Update camera with position, its forward, up and sideways vectors, dimensions
** and focal length (affects field of view)
*/

void			update_camera(t_camera *camera, float dims_focal_length[3],
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

void			update_player_camera(t_doom3d *app)
{
	t_vec3	forward_up_sideways[3];
	float	dims[2];
	float	focal_length;

	dims[0] = app->window->framebuffer->width / 2.0;
	dims[1] = app->window->framebuffer->height / 2.0;
	focal_length = Z_DIR * app->window->framebuffer->width * 0.7;
	ml_vector3_copy(app->player.forward, forward_up_sideways[0]);
	ml_vector3_copy(app->player.up, forward_up_sideways[1]);
	ml_vector3_copy(app->player.sideways, forward_up_sideways[2]);
	update_camera(app->active_scene->main_camera,
		(float [3]){dims[0], dims[1], focal_length},
		forward_up_sideways, app->player.pos);
}


/*
** Gets a new camera position and transforms its direction vectors with a lookat
** camera.
*/

void			update_third_person_camera(t_doom3d *app, t_vec3 pos)
{
	t_vec3	forward_up_sideways[3];
	float	dims[2];
	float	focal_length;
	t_mat4	look_at;

	dims[0] = app->window->framebuffer->width / 2.0;
	dims[1] = app->window->framebuffer->height / 2.0;
	focal_length = Z_DIR * app->window->framebuffer->width * 0.7;
	ml_matrix4_lookat(pos, app->player.pos, (t_vec3){0, Y_DIR, 0}, look_at);
	ml_vector3_sub(app->player.pos, pos, forward_up_sideways[0]);
	ml_vector3_normalize(forward_up_sideways[0], forward_up_sideways[0]);
	ml_matrix4_mul_vec3(look_at, (t_vec3){0, Y_DIR, 0}, forward_up_sideways[1]);
	ml_matrix4_mul_vec3(look_at, (t_vec3){X_DIR, 0, 0}, forward_up_sideways[2]);
	update_camera(app->active_scene->main_camera,
		(float [3]){dims[0], dims[1], focal_length},
		forward_up_sideways, pos);
}

/*
** To rotate camera around player we need to make its origin player's position
** and then apply rotations to the position.
*/

void			rotate_third_person_camera_horizontal(t_doom3d *app,
					float x_angle)
{
	t_vec3	new_pos;
	t_vec3	old_pos;
	t_mat4	rot_x;

	ml_vector3_sub(app->active_scene->third_person_camera->world_pos,
		app->player.pos, old_pos);
	ml_matrix4_rotation_x(ml_rad(x_angle), rot_x);
	ml_matrix4_mul_vec3(rot_x, old_pos, old_pos);
	ml_vector3_add(new_pos, app->player.pos, new_pos);
	update_third_person_camera(app, new_pos);
}

void			rotate_third_person_camera_vertical(t_doom3d *app,
					float y_angle)
{
	t_vec3	new_pos;
	t_vec3	old_pos;
	t_mat4	rot_y;

	ml_vector3_sub(app->active_scene->third_person_camera->world_pos,
		app->player.pos, old_pos);
	ml_matrix4_rotation_x(ml_rad(y_angle), rot_y);
	ml_matrix4_mul_vec3(rot_y, old_pos, old_pos);
	ml_vector3_add(new_pos, app->player.pos, new_pos);
	update_third_person_camera(app, new_pos);
}
