/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forces_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:49:15 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/20 17:42:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		forces_update_player(t_doom3d *app)
{
	// When player falls, check groundedness only then
	if (app->player.is_falling && player_is_grounded(app))
	{
		app->player.velocity[1] = 0;
		app->player.is_jumping = false;
		app->player.is_falling = false;
		app->player.is_grounded = true;
	}
	// If not jumping, nor falling, and player walks off a cliff and is not
	// grounded, player will then fall
	else if (!app->player.is_jumping && !app->player.is_falling &&
		!player_is_grounded(app))
	{
		app->player.is_falling = true;
		app->player.jump_force = 0.2;
	}
	// If player jumps and max_jump has gotten close to zero, stop jumping,
	// start falling
	if (app->player.is_jumping && app->player.jump_force < 0.2)
	{
		app->player.is_falling = true;
		app->player.is_jumping = false;
	}
	// If player is falling, limit fall speed.
	if (app->player.is_falling)
	{
		app->player.jump_force *= CONST_GRAVITY;
		if (app->player.jump_force >= PLAYER_JUMP_FORCE)
			app->player.jump_force = PLAYER_JUMP_FORCE;
		app->player.velocity[1] = app->player.jump_force;
	}
	// If player is jumping, decrease upwards velocity
	else if (app->player.is_jumping)
	{
		app->player.jump_force /= CONST_GRAVITY;
		app->player.velocity[1] = -app->player.jump_force;
	}
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
