/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 02:46:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 03:01:33 by ohakola          ###   ########.fr       */
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

	get_move_dir(app, move_dir, dir);
	ml_vector3_mul(dir, amount, dir);
	ml_vector3_add(app->player.velocity, dir, app->player.velocity);
}

void		handle_player_jump(t_doom3d *app)
{
	player_jump(app);
}

void		handle_player_crouch(t_doom3d *app, t_bool is_crouching)
{
	player_crouch(app, is_crouching);
}

void		handle_player_toggle_flight(t_doom3d *app)
{
	app->player.can_fly = !app->player.can_fly;
}
