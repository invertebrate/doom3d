/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_elevator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:13:24 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/31 02:29:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	set_test_patrol_pattern(t_npc *npc)
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
	npc->atk_pattern[1] = action_repeat;
}

void	npc_elevator(t_doom3d *app, t_npc *npc, t_3d_object *obj)
{
	npc->parent = obj;
	npc->type = npc_type_elevator;
	npc->speed = app->unit_size / 16;
	npc->rot_speed = 10;
	npc->state = 0;
	npc->hp = 1000;
	npc->advance = false;
	npc->physics_state = physics_state_not_applied;
	npc->atk_range = 0;
	npc->atk_dmg = 0;
	npc->atk_dur = 0;
	npc->vision_range = 0;
	npc->interest = 0;
	npc->max_interest = 0;
	npc->model_key = NPC_ELEVATOR_MODEL;
	npc->texture_key = NPC_ELEVATOR_TEXTURE;
	npc->normal_map_key = NPC_ELEVATOR_NORMM;
	npc->model_scale = 1;
	npc->animation_3d = NULL;
	ml_vector3_set(npc->velocity, 0, 0, 0);
	npc->atk_pattern_index = 0;
	set_attack_pattern(npc);
	set_test_patrol_pattern(npc);
}

void	elevator_go_to_next_node(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*elevator;

	if (!obj)
		return ;
	elevator = obj->params;
	elevator->speed = app->unit_size / 16;
}
