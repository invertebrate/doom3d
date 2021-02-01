/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/29 21:30:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void set_test_patrol_pattern(t_doom3d *app, t_npc *npc) //testing
{
	float	u = app->unit_size;
	npc->patrol_path_index = 0;
	npc->patrol_path[0][0] = -14 * u;
	npc->patrol_path[0][1] = 2 * u;
	npc->patrol_path[0][2] = -13 * u;
	npc->patrol_path[1][0] = -11 * u;
	npc->patrol_path[1][1] = 2 * u;
	npc->patrol_path[1][2] = 9 * u;
	npc->patrol_path[2][0] = 3 * u;
	npc->patrol_path[2][1] = 2 * u;
	npc->patrol_path[2][2] = 8 * u;
	npc->patrol_path[3][0] = 1 * u;
	npc->patrol_path[3][1] = 2 * u;
	npc->patrol_path[3][2] = -12 * u;
	npc->patrol_path[4][0] = INT32_MAX;
	npc->patrol_path[4][1] = INT32_MAX;
	npc->patrol_path[4][2] = INT32_MAX;
}

static void	set_attack_pattern(t_npc *npc)
{
	npc->atk_pattern[0] = action_wait;
	npc->atk_pattern[1] = action_projectile_rpg;
	npc->atk_pattern[2] = action_wait;
	npc->atk_pattern[3] = action_melee_basic;
	npc->atk_pattern[4] = action_melee_basic;
	npc->atk_pattern[5] = action_melee_basic;
	npc->atk_pattern[6] = action_melee_basic;
	npc->atk_pattern[7] = action_repeat;
}

void	npc_default(t_doom3d *app, t_npc *npc)
{
	npc->type = npc_type_default;
	npc->speed = app->unit_size / 8;
	npc->rot_speed = 10;
	npc->state = 0;
	npc->hp = 100;
	npc->advance = false;
	npc->atk_range = app->unit_size * 5;
	npc->atk_dmg = 10;
	npc->atk_dur = 500;
	npc->vision_range = app->unit_size * 10;
	npc->interest = 0;
	npc->max_interest = 100;
	npc->model_key = NPC_DEFAULT_MODEL;
	npc->texture_key = NPC_DEFAULT_TEXTURE;
	npc->normal_map_key = NPC_DEFAULT_NORMM;
	ml_vector3_set(npc->velocity, 0, 0, 0);
	npc->atk_pattern_index = 0;
	set_attack_pattern(npc);
	set_test_patrol_pattern(app, npc); //testing
}