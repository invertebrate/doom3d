/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:47:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/11 18:04:06 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_jump(t_doom3d *app)
{
	if (app->player.physics_state == physics_state_grounded)
	{
		app->player.velocity[1] -= app->player.jump_force * 0.9;
		app->player.velocity[0] = app->player.velocity[0] * 1.5;
		app->player.velocity[2] = app->player.velocity[2] * 1.5;
		app->player.physics_state = physics_state_jumping;
	}
	if (app->player.can_fly)
	{
		app->player.velocity[1] -= app->player.jump_force * 0.2;
		app->player.physics_state = physics_state_jumping;
	}
}
