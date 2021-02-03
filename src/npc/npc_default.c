/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/02/02 17:18:12 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void set_test_patrol_pattern(t_npc *npc) //testing
{
	npc->patrol_path_index = 0;
	npc->patrol_path[0] = NULL;
	npc->patrol_path[1] = NULL;
	npc->patrol_path[2] = NULL;
	npc->patrol_path[3] = NULL;
	npc->patrol_path[4] = NULL;
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
	set_test_patrol_pattern(npc); //testing
}