/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/29 23:51:02 by sotamursu        ###   ########.fr       */
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
	npc->atk_pattern[1] = action_melee_basic;
	npc->atk_pattern[2] = action_wait;
	npc->atk_pattern[3] = action_melee_basic;
	npc->atk_pattern[4] = action_wait;
	npc->atk_pattern[5] = action_melee_basic;
	npc->atk_pattern[6] = action_wait;
	npc->atk_pattern[7] = action_repeat;
}

/*
** monster01 variant differences
*/

void	npc_monster01(t_doom3d *app, t_npc *npc, int type)
{
	if (type == npc_type_monster01_a)
	{
		npc->texture_key = MONSTER01A_TEXTURE;
		npc->model_scale = 0.03;
		npc->type = type;
		npc->hp = 1000;
		npc->speed = app->unit_size / 4.2;
		npc->atk_range = app->unit_size * 9;
		npc->atk_dmg = 250;
	}
	if (type == npc_type_monster01_range)
	{
		npc->model_key = MONSTER01_MODEL;
		npc->texture_key = MONSTER01B_TEXTURE;
		npc->normal_map_key = MONSTER01_NORMM;
		npc->model_scale = 0.009;
		npc->hp = 200;
		npc->speed = app->unit_size / 3.3;
		npc->type = type;
		npc->advance = true;
	}
	if (type == npc_type_boss)
		npc_boss(app, npc, type);
}

static void	npc_default_vars(t_doom3d *app, t_npc *npc)
{
	float	cy;
	float	sy;
	float	offset;
	float	angle;

	offset = -90;
	if (app->final_boss_bubblegum)
		offset = +90;
	angle = (npc->angle - offset) * M_PI / 180;
	cy = cos(angle);
	sy = sin(angle);
	npc->dir[1] = 0;
	npc->dir[0] = cy;
	npc->dir[2] = sy;
	npc->rot_speed = 10;
	npc->state = 0;
	npc->hp = 100;
	npc->advance = true;
	npc->physics_state = physics_state_grounded;
}

void	npc_default(t_doom3d *app, t_npc *npc, t_3d_object *obj)
{
	t_animation_3d	*dummy;

	error_check(!(dummy = (t_animation_3d *)ft_calloc(sizeof(t_animation_3d))),
		"Failed to malloc for dummy in npc_default.");
	npc->parent = obj;
	npc->type = npc_type_monster01;
	npc->speed = app->unit_size / 3.5;
	npc_default_vars(app, npc);
	npc->atk_range = app->unit_size * 6;
	npc->atk_dmg = 100;
	npc->atk_dur = 8000;
	npc->vision_range = app->unit_size * 50;
	npc->hearing_range = app->unit_size * 20;
	npc->interest = 0;
	npc->max_interest = 100;
	npc->model_scale = 0.01;
	npc->model_key = MONSTER01_MODEL;
	npc->texture_key = MONSTER01_TEXTURE;
	npc->normal_map_key = MONSTER01_NORMM;
	npc->animation_3d = dummy;
	ml_vector3_set(npc->velocity, 0, 0, 0);
	npc->atk_pattern_index = 0;
	set_attack_pattern(npc);
	set_test_patrol_pattern(npc);
}
