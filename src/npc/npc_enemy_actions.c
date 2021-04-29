/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 19:43:09 by veilo             #+#    #+#             */
/*   Updated: 2021/04/29 19:46:11 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
**	This is an animation event trigger function that is custom made for enemy
**	death animation only. It is triggered when death animation is finished
**	and cleanly removes the enemy.
*/

static void	npc_death_event_ontrigger(t_doom3d *app, void** params)
{
	push_custom_event(app, event_object_delete, params[0], params[1]);
	LOG_DEBUG("Enemy npc removed by death animation trigger event.");
}

/*
**	This is sort of a dummy function since it only prints. An event function is
**	required for an animation instance to play.
*/

static void	npc_attack_event_ontrigger(t_doom3d *app, void** params)
{
	if (app->is_debug)
		LOG_DEBUG("Enemy finihed attacking.");
	(void)params;
}

void		init_anim_instance_attack(t_3d_object *obj,
										t_anim_3d_instance *inst)
{

	inst->active = true;
	inst->anim_clip = anim_3d_type_attack;
	inst->f_event = npc_attack_event_ontrigger;
	inst->params[0] = obj;
	inst->params[1] = NULL;
	inst->params[2] = NULL;
	inst->start_frame = 0;
	inst->trigger_time = 1.0;
	inst->event_triggered = false;
}

void		init_anim_instance_death(t_3d_object *obj, t_anim_3d_instance *inst)
{

	inst->active = true;
	inst->anim_clip = anim_3d_type_death;
	inst->f_event = npc_death_event_ontrigger;
	inst->params[0] = obj;
	inst->params[1] = NULL;
	inst->params[2] = NULL;
	inst->start_frame = 0;
	inst->trigger_time = 1.0;
	inst->event_triggered = false;
}
