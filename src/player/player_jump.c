/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:47:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/31 22:18:56 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_jump(t_doom3d *app)
{
	if (app->player.physics_state == physics_state_grounded)
	{
		app->player.velocity[1] -= app->player.jump_force * 0.9;
		app->player.velocity[0] = app->player.velocity[0] * 1.65;
		app->player.velocity[2] = app->player.velocity[2] * 1.65;
		app->player.physics_state = physics_state_jumping;
		app->stats.times_jumped++;
	}
	if (app->player.can_fly)
	{
		app->player.velocity[1] -= app->player.jump_force * 0.2;
		app->player.physics_state = physics_state_jumping;
	}
}
