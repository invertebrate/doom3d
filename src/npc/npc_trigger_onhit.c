/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_trigger_onhit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:35:16 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/31 23:35:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

 void				npc_death_event_ontrigger(t_doom3d *app, void** params)
{
	push_custom_event(app, event_object_delete, params[0], params[1]);
	LOG_DEBUG("Enemy npc removed by death animation trigger event.");
}

 void	init_anim_instance_death(t_3d_object *obj, t_anim_3d_instance *inst)
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

void		npc_trigger_onhit(t_doom3d *app, t_3d_object *obj, int damage)
{
	t_npc				*npc;
	t_anim_3d_instance	anim_instance_death;

	npc = obj->params;
	npc->hp -= damage;
	if (npc->state == state_death_anim)
		return ;
	if (npc->type != npc_type_elevator)
		npc->state = state_attack;
	npc->interest = npc->max_interest;
	if (npc->hp <= 0 && npc->state)
	{
		init_anim_instance_death(obj, &anim_instance_death);
		npc->state = state_death_anim;
		anim_3d_clip_play(app, obj, &anim_instance_death);
	}
}