/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:47:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/07 00:02:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_jump(t_doom3d *app)
{
	if (!app->player.can_fly &&
		app->player.physics_state == physics_state_grounded)
		app->player.velocity[1] -= PLAYER_JUMP_FORCE * 1.0;
	if (app->player.can_fly)
	{
		app->player.velocity[1] -= PLAYER_JUMP_FORCE * 0.2;
	}
}