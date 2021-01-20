/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forces_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:49:15 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/20 20:49:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		forces_update_player(t_doom3d *app)
{
	float		deceleration;

	if (app->player.is_falling && player_is_grounded(app))
	{
		app->player.velocity[1] = 0;
		app->player.is_jumping = false;
		app->player.is_falling = false;
		app->player.is_grounded = true;
	}
	else if (!app->player.is_jumping && !app->player.is_falling &&
		!player_is_grounded(app))
		app->player.is_falling = true;
	if (app->player.is_jumping && app->player.velocity[1] >= 0.0)
	{
		app->player.is_falling = true;
		app->player.is_jumping = false;
	}
	if (app->player.is_falling || app->player.is_jumping)
		app->player.velocity[1] += 0.2;
	if (!app->player.is_grounded)
		deceleration = 1.005;
	else
		deceleration = 1.2;
	ml_vector3_copy((t_vec3){app->player.velocity[0] / deceleration,
		app->player.velocity[1], app->player.velocity[2] / deceleration},
		app->player.velocity);
}

void		forces_update_object(t_doom3d *app, t_3d_object *target)
{
	t_npc	*npc;

	npc = target->params;
	l3d_3d_object_translate(target,
		npc->velocity[0], npc->velocity[1], npc->velocity[2]);
	if (obj_is_grounded(app, target))
		npc->velocity[1] = 0;
	else
	{
		npc->velocity[1] += app->info.delta_time * CONST_SPEED;
	}
}
