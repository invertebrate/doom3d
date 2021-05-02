/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 02:46:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 23:20:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_player_rotate(t_doom3d *app, int32_t xrel, int32_t yrel)
{
	player_rotate_vertical(app, -(float)yrel * 0.3);
	player_rotate_horizontal(app, (float)xrel * 0.3);
}

void		handle_player_move(t_doom3d *app, t_move move_dir, int32_t amount)
{
	t_vec3	dir;

	ml_vector3_set_all(dir, 0.0);
	get_move_dir(app, move_dir, dir);
	if (app->player.physics_state != physics_state_grounded &&
		app->player.can_fly)
		ml_vector3_mul(dir, (float)amount / 5.0, dir);
	else
		ml_vector3_mul(dir, amount, dir);
	ml_vector3_add(app->player.velocity, dir, app->player.velocity);
}
