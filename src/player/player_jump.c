/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:47:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/09 16:31:28 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_jump(t_doom3d *app)
{
	if (app->player.physics_state == physics_state_grounded)
	{
		app->player.velocity[1] -= PLAYER_JUMP_FORCE * 1.0;
		app->player.physics_state = physics_state_jumping;
	}
	if (app->player.can_fly)
	{
		app->player.velocity[1] -= PLAYER_JUMP_FORCE * 0.2;
		app->player.physics_state = physics_state_jumping;
	}
}
