/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:47:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/02/09 10:02:22 by ahakanen         ###   ########.fr       */
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
		ft_printf("player.is_flying = %d\n", app->player.is_flying);//test
	}
}