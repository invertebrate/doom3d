/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:47:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/12 19:32:15 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_jump(t_doom3d *app)
{
	if (app->player.physics_state == physics_state_grounded)
		app->player.velocity[1] -= PLAYER_JUMP_FORCE * 1.0;
	if (app->player.can_fly)
	{
		app->player.velocity[1] -= PLAYER_JUMP_FORCE * 0.2;
	}
}
