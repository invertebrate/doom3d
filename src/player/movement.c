/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/20 17:32:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		player_rotate(t_doom3d *app)
{
	t_mat4	rotation_y;
	t_mat4	rotation_x;
	t_mat4	rotation;

	ml_matrix4_rotation_x(ml_rad(app->player.rot_y), rotation_y);
	ml_matrix4_rotation_y(ml_rad(app->player.rot_x), rotation_x);
	ml_matrix4_mul(rotation_x, rotation_y, rotation);
	ml_matrix4_mul_vec3(rotation, (t_vec3){0, 0, Z_DIR}, app->player.forward);
	ml_matrix4_mul_vec3(rotation, (t_vec3){X_DIR, 0, 0}, app->player.sideways);
	ml_matrix4_mul_vec3(rotation, (t_vec3){0, Y_DIR, 0}, app->player.up);
	ml_matrix4_inverse(rotation, app->player.inv_rotation);
}

void			player_rotate_vertical(t_doom3d *app, float angle)
{
	app->player.rot_y += app->player.rot_speed * angle;
	if (app->player.rot_y > 90.0)
		app->player.rot_y = 90.0;
	if (app->player.rot_y < -90.0)
		app->player.rot_y = -90.0;
	player_rotate(app);
}

void			player_rotate_horizontal(t_doom3d *app, float angle)
{
	app->player.rot_x += app->player.rot_speed * angle;
	player_rotate(app);
}

void			get_move_dir(t_doom3d *app, t_move dir_option, t_vec3 dir)
{
	t_vec3		forward;
	t_vec3		sideways;
	t_vec3		up;
	t_mat4		rotation_x;

	ml_matrix4_rotation_y(ml_rad(app->player.rot_x), rotation_x);
	ml_matrix4_mul_vec3(rotation_x, (t_vec3){0, 0, Z_DIR}, forward);
	ml_matrix4_mul_vec3(rotation_x, (t_vec3){X_DIR, 0, 0}, sideways);
	ml_vector3_copy((t_vec3){0, Y_DIR, 0}, up);
	if (dir_option == move_forward)
		ml_vector3_mul(forward, 1, dir);
	else if (dir_option == move_backward)
		ml_vector3_mul(forward, -1, dir);
	else if (dir_option == move_strafe_left)
		ml_vector3_mul(sideways, -1, dir);
	else if (dir_option == move_strafe_right)
		ml_vector3_mul(sideways, 1, dir);
	else if (dir_option == move_downwards)
		ml_vector3_mul(up, 1, dir);
	else if (dir_option == move_upwards)
		ml_vector3_mul(up, -1, dir);
}

void			player_move(t_doom3d *app)
{
	t_vec3		add;
	float		speed;
	float		deceleration;

	app->player.is_moving = true;
	speed = (app->player.is_running && !app->player.is_jumping ?
		app->player.speed * 1.5 : app->player.speed) *
			app->info.delta_time * CONST_SPEED;
	ml_vector3_mul(app->player.velocity, speed, add);
	// collision_limit_player(app, add);
	ml_vector3_add(app->player.pos, add, app->player.pos);
	ml_matrix4_translation(app->player.pos[0],
		app->player.pos[1], app->player.pos[2], app->player.translation);
	ml_matrix4_inverse(app->player.translation, app->player.inv_translation);
	if (!app->player.is_grounded)
		deceleration = 1.005;
	else
		deceleration = 1.2;
	ml_vector3_copy((t_vec3){app->player.velocity[0] / deceleration,
		app->player.velocity[1], app->player.velocity[2] / deceleration},
		app->player.velocity);
	ml_vector3_print(app->player.pos);
}

void			editor_vertical_move(t_doom3d *app, float speed)
{
	t_vec3		add;
	t_vec3		up;

	ml_vector3_copy((t_vec3){0, Y_DIR, 0}, up);
	ml_vector3_mul(up, speed, add);
	ml_vector3_add(app->player.pos, add, app->player.pos);
	ml_matrix4_translation(app->player.pos[0],
		app->player.pos[1], app->player.pos[2], app->player.translation);
	ml_matrix4_inverse(app->player.translation, app->player.inv_translation);
}
