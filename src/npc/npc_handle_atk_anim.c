/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_handle_atk_anim.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:27:37 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/25 18:45:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_attack(t_doom3d *app, t_3d_object *npc_obj, t_npc *npc)
{
	t_vec3	dist;

	if (npc->atk_pattern[npc->atk_pattern_index] == action_melee_basic)
	{
		ml_vector3_sub(app->player.pos, npc_obj->position, dist);
		if (ml_vector3_mag(dist) < npc->atk_range)
			player_onhit(app, npc->atk_dmg);
	}
	if (npc->atk_pattern[npc->atk_pattern_index] == action_projectile_rpg)
	{
		push_custom_event(app, event_npc_shoot_projectile, npc_obj, NULL);
		if (app->settings.is_debug)
			LOG_DEBUG("Npc %d shot projectile", npc_obj->id);
	}
}

void	handle_atk_anim(t_doom3d *app, t_3d_object *npc_obj)
{
	uint32_t			new_time;
	t_npc				*npc;
	t_anim_3d_instance	attack_inst;

	npc = npc_obj->params;
	init_anim_instance_attack(npc_obj, &attack_inst);
	if (npc->animation_3d->current_anim_instance->active == false)
		anim_3d_clip_play(app, npc_obj, &attack_inst);
	new_time = SDL_GetTicks();
	npc->atk_timer += new_time - npc->atk_start;
	if (npc->atk_timer > npc->atk_dur)
	{
		handle_attack(app, npc_obj, npc);
		npc->state = state_attack;
	}
}
