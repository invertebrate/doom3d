/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:09:05 by veilo             #+#    #+#             */
/*   Updated: 2021/05/30 20:41:51 by veilo            ###   ########.fr       */
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

void	player_cap_velocity(t_doom3d *app)
{
	t_player	*player;

	player = &app->player;
	if (fabs(player->velocity[0]) > PLAYER_MAX_SPEED)
		player->velocity[0] = (player->velocity[0]
				/ fabs(player->velocity[0])) * (PLAYER_MAX_SPEED);
	if (fabs(player->velocity[1]) > PLAYER_MAX_SPEED)
		player->velocity[1] = (player->velocity[1]
				/ fabs(player->velocity[1])) * (PLAYER_MAX_SPEED);
	if (fabs(player->velocity[2]) > PLAYER_MAX_SPEED)
		player->velocity[2] = (player->velocity[2]
				/ fabs(player->velocity[2])) * (PLAYER_MAX_SPEED);
}
