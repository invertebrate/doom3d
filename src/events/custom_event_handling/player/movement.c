/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 02:46:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/31 22:38:22 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_player_rotate(t_doom3d *app, int32_t xrel, int32_t yrel)
{
	player_rotate_vertical(app, -(float)yrel * 0.3);
	player_rotate_horizontal(app, (float)xrel * 0.3);
}

static void	handle_non_physics_movement(t_doom3d *app, t_move move_dir,
				t_vec3 dir, int32_t amount)
{
	t_vec3	temp;

	ml_vector3_set_all(temp, 0.0);
	if (move_dir == move_forward)
	{
		ml_vector3_mul(app->player.forward, amount * 5, temp);
		ml_vector3_add(dir, temp, dir);
	}
	if (move_dir == move_backward)
	{
		ml_vector3_mul(app->player.forward, -amount * 5, temp);
		ml_vector3_add(dir, temp, dir);
	}
	if (move_dir == move_strafe_left)
	{
		ml_vector3_mul(app->player.sideways, -amount * 5, temp);
		ml_vector3_add(dir, temp, dir);
	}
	if (move_dir == move_strafe_right)
	{
		ml_vector3_mul(app->player.sideways, amount * 5, temp);
		ml_vector3_add(dir, temp, dir);
	}
}

void	handle_player_move(t_doom3d *app, t_move move_dir, int32_t amount)
{
	t_vec3	dir;

	ml_vector3_set_all(dir, 0.0);
	if (app->player.physics_state == physics_state_not_applied)
		handle_non_physics_movement(app, move_dir, dir, amount);
	else
	{
		get_move_dir(app, move_dir, dir);
		if (app->player.physics_state != physics_state_grounded
			&& app->player.can_fly)
			ml_vector3_mul(dir, (float)amount / 5.0, dir);
		else
			ml_vector3_mul(dir, amount, dir);
	}
	ml_vector3_add(app->player.velocity, dir, app->player.velocity);
}

void	handle_toggle_player_collision(t_doom3d *app)
{
	if (app->player.physics_state == physics_state_not_applied)
		app->player.physics_state = physics_state_not_grounded;
	else
	{
		app->player.physics_state = physics_state_not_applied;
		app->stats.times_cheated++;
	}
}
