/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/09 15:58:30 by ahakanen         ###   ########.fr       */
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
	npc->atk_pattern[1] = action_melee_basic;
	npc->atk_pattern[2] = action_wait;
	npc->atk_pattern[3] = action_melee_basic;
	npc->atk_pattern[4] = action_wait;
	npc->atk_pattern[5] = action_melee_basic;
	npc->atk_pattern[6] = action_wait;
	npc->atk_pattern[7] = action_repeat;
}

void	npc_default(t_doom3d *app, t_npc *npc, t_3d_object *obj)
{
	t_animation_3d	*dummy;

	error_check(!(dummy= (t_animation_3d*)ft_calloc(sizeof(t_animation_3d))),
		"Failed to malloc for dummy in npc_default.");
	npc->parent = obj;
	npc->type = npc_type_default;
	npc->speed = app->unit_size / 3.5;
	npc->dir[0] = 0;
	npc->dir[1] = 0;
	npc->dir[2] = 0;
	npc->rot_speed = 10;
	npc->state = 0;
	npc->hp = 100;
	npc->advance = true;
	npc->physics_state = physics_state_grounded;
	ml_vector3_set_all(npc->dir, 0.0);
	npc->atk_range = app->unit_size * 6;
	npc->atk_dmg = 10;
	npc->atk_dur = 500;
	npc->vision_range = app->unit_size * 25;
	npc->hearing_range = app->unit_size * 50;
	npc->interest = 0;
	npc->max_interest = 100;
	npc->model_scale = 0.01;
	npc->model_key = NPC_DEFAULT_MODEL;
	npc->texture_key = NPC_DEFAULT_TEXTURE;
	npc->normal_map_key = NPC_DEFAULT_NORMM;
	npc->animation_3d = dummy; //segfaults when dummy no exists
	// npc->animation_3d = NULL;
	ml_vector3_set(npc->velocity, 0, 0, 0);
	npc->atk_pattern_index = 0;
	set_attack_pattern(npc);
	set_test_patrol_pattern(npc); //testing
}
