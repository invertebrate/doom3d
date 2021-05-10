/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:09:05 by veilo             #+#    #+#             */
/*   Updated: 2021/05/10 17:09:22 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

float	get_movement_speed(t_doom3d *app)
{
	float		speed;

	if (app->player.is_running
		&& app->player.physics_state != physics_state_not_grounded)
		speed = app->player.speed * 1.5;
	else if (app->player.is_crouching
		&& app->player.physics_state != physics_state_not_grounded)
		speed = app->player.speed * 0.5;
	else
		speed = app->player.speed;
	speed = speed * app->info.delta_time * CONST_SPEED;
	return (speed);
}
