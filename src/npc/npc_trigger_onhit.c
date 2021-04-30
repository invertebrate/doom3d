/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_trigger_onhit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:35:16 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/30 17:32:29 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_sound_effect(t_doom3d *app, t_npc *npc, t_3d_object *obj)
{
	if (npc->type != npc_type_elevator)
	{
		npc->state = state_attack;
		if (npc->type == npc_type_crate)
			push_custom_event(app, event_effect_play, (void*)sf_crate_break,
				s_ini(0, 1, st_game, distance_vol(0.8f,
				sound_mag(app->player.pos, obj->position), -1)));
		else
			push_custom_event(app, event_effect_play, (void*)sf_monster_hurt,
				s_ini(0, 1, st_game, distance_vol(0.8f,
				sound_mag(app->player.pos, obj->position), -1)));
	}
}

void		npc_trigger_onhit(t_doom3d *app, t_3d_object *obj, int damage)
{
	t_npc				*npc;
	t_anim_3d_instance	anim_instance_death;

	npc = obj->params;
	npc->hp -= damage;
	if (npc->state == state_death_anim)
		return ;
	handle_sound_effect(app, npc, obj);
	npc->interest = npc->max_interest;
	if (npc->hp <= 0 && npc->type == npc_type_crate)
		push_custom_event(app, event_object_delete, obj, NULL);
	if (npc->hp <= 0 && npc->state)
	{
		init_anim_instance_death(obj, &anim_instance_death);
		npc->state = state_death_anim;
		anim_3d_clip_play(app, obj, &anim_instance_death);
	}
}
