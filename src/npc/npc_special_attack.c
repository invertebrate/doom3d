/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_special_attack.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/30 00:07:12 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_special_spawn(t_doom3d *app, t_3d_object *npc_obj, t_npc *npc)
{
	t_vec3	offset;
	t_vec3	pos;
	float	a;
	float	b;

	app->final_boss_bubblegum = true;
	a = (0.15 * l3d_rand_d() - 0.075) * app->unit_size;
	b = (0.15 * l3d_rand_d() - 0.075) * app->unit_size;
	offset[0] = a;
	offset[1] = 0;
	offset[2] = b;
	ml_vector3_mul(offset, 100, offset);
	ml_vector3_add(npc_obj->position, offset, pos);
	if (npc->atk_pattern[npc->atk_pattern_index] == action_spawn_a)
		npc_spawn(app, pos, 0, npc_type_monster01);
	else
		npc_spawn(app, pos, 0, npc_type_monster01_range);
	push_custom_event(app, event_effect_play, (void *)sf_spawn,
		s_ini(0, 1, st_game, distance_vol(0.8f,
				sound_mag(app->player.pos, npc_obj->position), -1)));
	app->final_boss_bubblegum = false;
}
