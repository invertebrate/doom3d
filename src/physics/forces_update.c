/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forces_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:49:15 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/06 23:33:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Calculates forces resulting in velocity. Deceleration for horizontal forces
** gravity for vertical. Also updates e.g npc's state regardind jump, fall or
** groundedness.
** The forces (velocity) are applied to player position in player_move.
*/

void		forces_update_player(t_doom3d *app)
{
	float		deceleration;

	if (app->player.physics_state != physics_state_editor_fly)
	{
		if (app->player.physics_state == physics_state_grounded)
			app->player.velocity[1] = 0;
		if ((app->player.physics_state == physics_state_jumping ||
			app->player.physics_state == physics_state_falling) &&
			app->player.velocity[1] < PLAYER_MAX_SPEED)
			app->player.velocity[1] += 0.2;
		if (app->player.physics_state == physics_state_flying &&
			app->player.velocity[1] > -PLAYER_MAX_SPEED)
			app->player.velocity[1] -= 0.2;
	}
	if (app->player.physics_state != physics_state_grounded &&
		app->player.physics_state != physics_state_editor_fly)
		deceleration = 1.005;
	else
		deceleration = 1.2;
	ml_vector3_copy((t_vec3){app->player.velocity[0] / deceleration,
		app->player.velocity[1], app->player.velocity[2] / deceleration},
		app->player.velocity);
	if (app->player.physics_state == physics_state_editor_fly)
		app->player.velocity[1] = app->player.velocity[1] / deceleration;
}

static void	forces_update_npc(t_3d_object *npc_object)
{
	t_npc		*npc;
	float		deceleration;

	npc = npc_object->params;
	if (npc->physics_state != physics_state_editor_fly)
	{
		if (npc->physics_state == physics_state_grounded)
			npc->velocity[1] = 0;
		if ((npc->physics_state == physics_state_jumping ||
			npc->physics_state == physics_state_falling) &&
			npc->velocity[1] < PLAYER_MAX_SPEED)
			npc->velocity[1] += 0.2;
		if (npc->physics_state == physics_state_flying &&
			npc->velocity[1] > -PLAYER_MAX_SPEED)
			npc->velocity[1] -= 0.2;
	}
	if (npc->physics_state != physics_state_grounded &&
		npc->physics_state != physics_state_editor_fly)
		deceleration = 1.000;
	else
		deceleration = 1.2;
	ml_vector3_copy((t_vec3){npc->velocity[0] / deceleration,
		npc->velocity[1], npc->velocity[2] / deceleration},
		npc->velocity);
}

/*
** Calculates forces resulting in velocity. Deceleration for horizontal forces
** gravity for vertical. Also updates e.g npc's state regardind jump, fall or
** groundedness.
** The forces (velocity) are then applied on the position of the object.
*/

void		update_object_forces(t_doom3d *app, t_3d_object *obj)
{
	t_vec3	velocity;
	t_vec3	add;

	if (obj->type == object_type_npc)
	{
		forces_update_npc(obj);
		ml_vector3_copy(((t_npc*)obj->params)->velocity, velocity);
		ml_vector3_mul(velocity, app->info.delta_time * CONST_SPEED, add);
		l3d_3d_object_translate(obj, add[0], add[1], add[2]);
	}
}

void			update_object_physics_state(t_doom3d *app, t_3d_object *obj)
{
	t_npc			*npc;
	t_physics_state	prev_state;
	t_bool			is_grounded;
	// const char		*physics_state;

	if (obj->type == object_type_npc)
	{
		npc = obj->params;
		prev_state = npc->physics_state;
		if (npc->velocity[1] < 0)
		{
			if (npc->physics_state != physics_state_jumping)
				npc->physics_state = physics_state_flying;
			else
				npc->physics_state = physics_state_jumping;
		}
		else
		{
			is_grounded = obj_is_grounded(app, obj);
			if (npc->velocity[1] >= 0 && !is_grounded &&
				npc->physics_state != physics_state_flying)
				npc->physics_state = physics_state_falling;
			if (is_grounded && npc->physics_state != physics_state_jumping)
				npc->physics_state = physics_state_grounded;	
		}
		// !Uncomment below if you want to debug npc physics state
		// if (npc->physics_state != prev_state && app->is_debug)
		// {
		// 	physics_state = "UNKNOWN";
		// 	if (npc->physics_state == physics_state_jumping)
		// 		physics_state = "JUMPING";
		// 	else if (npc->physics_state == physics_state_flying)
		// 		physics_state = "FLYING";
		// 	else if (npc->physics_state == physics_state_falling)
		// 		physics_state = "FALLING";
		// 	else if (npc->physics_state == physics_state_grounded)
		// 		physics_state = "GROUNDED";
		// 	LOG_DEBUG("Player physics state %s", physics_state);
		// }
	}
}