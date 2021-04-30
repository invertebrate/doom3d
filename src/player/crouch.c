/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crouch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:59:19 by ahakanen          #+#    #+#             */
/*   Updated: 2021/02/03 14:03:26 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_crouch(t_doom3d *app, t_bool toggle)
{
	if (toggle)
	{
		app->player.player_height = PLAYER_HEIGHT_CROUCH * app->unit_size;
		app->player.is_crouching = true;
	}
	else
	{
		app->player.player_height = PLAYER_HEIGHT * app->unit_size;
		app->player.aabb.size[1] = app->player.player_height;
		player_update_aabb(&app->player);
		if (player_hits_ceiling(app))
		{
			app->player.player_height = PLAYER_HEIGHT_CROUCH * app->unit_size;
		}
		else
			app->player.is_crouching = false;
	}
	app->player.aabb.size[1] = app->player.player_height;
	player_update_aabb(&app->player);
}