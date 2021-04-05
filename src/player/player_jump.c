/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:47:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/05 18:15:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_jump(t_doom3d *app)
{
	if (app->player.is_grounded)
	{
		app->player.is_grounded = false;
		app->player.is_jumping = true;
		app->player.is_falling = false;
		app->player.velocity[1] -= PLAYER_JUMP_FORCE * 1.25;
	}
	if (!app->player.is_grounded && app->player.can_fly)
	{
		app->player.is_flying = (app->player.is_flying + 1) % 2;
		if (app->is_debug)
			LOG_INFO("Player is flying: %d", app->player.is_flying);
	}
}