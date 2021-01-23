/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forces_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:49:15 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/23 15:37:52 by ohakola          ###   ########.fr       */
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
	if ((app->player.is_falling || app->player.is_jumping) &&
		app->player.velocity[1] < PLAYER_MAX_SPEED)
		app->player.velocity[1] += 0.2;
	if (!app->player.is_grounded &&
		app->active_scene->scene_id != scene_id_editor3d)
		deceleration = 1.005;
	else
		deceleration = 1.2;
	if (app->active_scene->scene_id == scene_id_editor3d)
		app->player.velocity[1] = 0;
	ml_vector3_copy((t_vec3){app->player.velocity[0] / deceleration,
		app->player.velocity[1], app->player.velocity[2] / deceleration},
		app->player.velocity);
}

static void	forces_update_npc(t_doom3d *app, t_3d_object *npc_object)
{
	t_npc		*npc;
	float		deceleration;

	npc = npc_object->params;
	if (npc->is_falling && obj_is_grounded(app, npc_object))
	{
		npc->velocity[1] = 0;
		npc->is_jumping = false;
		npc->is_falling = false;
		npc->is_grounded = true;
	}
	else if (!npc->is_jumping && !npc->is_falling &&
		!obj_is_grounded(app, npc_object))
	{
		npc->is_falling = true;
	}
	if (npc->is_jumping && npc->velocity[1] >= 0.0)
	{
		npc->is_falling = true;
		npc->is_jumping = false;
	}
	if ((npc->is_falling || npc->is_jumping) &&
		app->player.velocity[1] < PLAYER_MAX_SPEED)
		npc->velocity[1] += 0.2;
	if (!npc->is_grounded)
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

void		forces_update_object(t_doom3d *app, t_3d_object *obj)
{
	t_vec3	velocity;
	t_vec3	add;

	if (obj->type == object_type_npc)
	{
		forces_update_npc(app, obj);
		ml_vector3_copy(((t_npc*)obj->params)->velocity, velocity);
		ml_vector3_mul(velocity, app->info.delta_time * CONST_SPEED, add);
		l3d_3d_object_translate(obj, add[0], add[1], add[2]);
	}
}
