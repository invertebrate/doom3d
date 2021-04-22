/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_crate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:13:24 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/22 19:22:05 by ahakanen         ###   ########.fr       */
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
	npc->atk_pattern[1] = action_repeat;
}

void	npc_crate(t_doom3d *app, t_npc *npc, t_3d_object *obj)
{
	npc->parent = obj;
	npc->type = npc_type_crate;
	npc->speed = 0;
	npc->rot_speed = 0;
	npc->state = 0;
	npc->hp = 20;
	npc->advance = false;
	npc->physics_state = physics_state_not_applied;
	npc->atk_range = 0;
	npc->atk_dmg = 0;
	npc->atk_dur = 0;
	npc->vision_range = 0;
	npc->interest = 0;
	npc->max_interest = 0;
	npc->model_key = NPC_ELEVATOR_MODEL;
	npc->texture_key = "assets/textures/crate.bmp";
	npc->normal_map_key = NPC_ELEVATOR_NORMM;
	npc->model_scale = 1;
	npc->animation_3d = NULL;
	ml_vector3_set(npc->velocity, 0, 0, 0);
	npc->atk_pattern_index = 0;
	set_attack_pattern(npc);
	set_test_patrol_pattern(npc); //testing
	(void)app;
}
