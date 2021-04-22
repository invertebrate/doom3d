/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_ranged.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:36:00 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/09 15:47:40 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void set_test_patrol_pattern(t_npc *npc) //testing
{
	int	i;

	npc->patrol_path_index = 0;
	i = -1;
	while (++i < MAX_PATROL_NODES + 1)
		npc->patrol_path[i] = NULL;
	npc->atk_pattern_index = 0;
	i = -1;
	while (++i < MAX_PATH_NODE_NETWORK_SIZE + 1)
		npc->attack_path[i] = NULL;
}

static void	set_attack_pattern(t_npc *npc)
{
	npc->atk_pattern[0] = action_wait;
	npc->atk_pattern[1] = action_projectile_rpg;
	npc->atk_pattern[2] = action_wait;
	npc->atk_pattern[3] = action_melee_basic;
	npc->atk_pattern[4] = action_wait;
	npc->atk_pattern[5] = action_melee_basic;
	npc->atk_pattern[6] = action_wait;
	npc->atk_pattern[7] = action_repeat;
}

void	npc_ranged(t_doom3d *app, t_npc *npc, t_3d_object *obj)
{
	t_animation_3d	*dummy;

	error_check(!(dummy= (t_animation_3d*)ft_calloc(sizeof(t_animation_3d))),
		"Failed to malloc for dummy in npc_ranged.");
	npc->parent = obj;
	npc->type = npc_type_monster02;
	npc->speed = app->unit_size / 8;
	npc->rot_speed = 10;
	npc->state = 0;
	npc->hp = 100;
	npc->advance = false;
	npc->physics_state = physics_state_grounded;
	ml_vector3_set_all(npc->dir, 0.0);
	npc->atk_range = app->unit_size * 5;
	npc->atk_dmg = 10;
	npc->atk_dur = 500;
	npc->vision_range = app->unit_size * 25;
	npc->hearing_range = app->unit_size * 50;
	npc->interest = 0;
	npc->max_interest = 100;
	npc->model_scale = 0.0065;
	npc->model_key = NPC_MONSTER02_MODEL;
	npc->texture_key = NPC_MONSTER02_TEXTURE;
	npc->normal_map_key = NPC_MONSTER02_NORMM;
	npc->animation_3d = dummy;
	ml_vector3_set(npc->velocity, 0, 0, 0);
	set_attack_pattern(npc);
	set_test_patrol_pattern(npc); //testing
}