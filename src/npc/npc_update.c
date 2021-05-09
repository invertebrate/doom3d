/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:21:49 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/09 15:14:46 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_attack_init(t_doom3d *app, t_3d_object *npc_obj,
													t_npc *npc, float dist)
{
	if (dist < npc->atk_range / 2
		&& npc->atk_pattern[npc->atk_pattern_index] == action_melee_basic)
	{
		npc->atk_timer = 0;
		npc->atk_start = SDL_GetTicks();
		npc->state = state_atk_anim;
	}
	if (npc->atk_pattern[npc->atk_pattern_index] == action_projectile_rpg
		&& npc_has_line_of_sight(app, npc_obj))
	{
		npc->atk_timer = 0;
		npc->atk_start = SDL_GetTicks();
		npc->state = state_atk_anim;
	}
}

static void	handle_state_idle(t_doom3d *app, t_3d_object *npc_obj, t_npc *npc,
															float dist)
{
	if (dist < npc->vision_range
		&& npc_has_line_of_sight(app, npc_obj))
	{
		npc->state = state_attack;
		push_custom_event(app,
			event_effect_play, (void *)sf_monster_alert, s_ini(0, 1, st_game,
				distance_vol(0.8f,
					sound_mag(app->player.pos, npc_obj->position), -1)));
	}
	npc_get_dir_to_next_waypoint(app, npc_obj);
}

static void	handle_line_of_sight(t_doom3d *app, t_3d_object *npc_obj,
												t_npc *npc, t_vec3 diff)
{
	if (!npc_has_line_of_sight(app, npc_obj))
	{
		if (!npc->attack_path[0])
			npc_find_path(app, npc, npc_obj->position, app->player.pos);
		if (npc_get_dir_to_next_atk(app, npc_obj))
			npc_find_path(app, npc, npc_obj->position, app->player.pos);
	}
	else
	{
		ft_memset(npc->attack_path, 0, sizeof(t_3d_object *)
			* MAX_PATH_NODE_NETWORK_SIZE);
		ml_vector3_normalize(diff, npc->dir);
	}
}

static void	handle_state_attack(t_doom3d *app, t_3d_object *npc_obj, t_npc *npc,
															t_vec3 diff)
{
	float	dist;

	dist = ml_vector3_mag(diff);
	npc->atk_pattern_index++;
	if (npc->atk_pattern[npc->atk_pattern_index] == action_repeat)
		npc->atk_pattern_index = 0;
	if (npc->atk_pattern[npc->atk_pattern_index] == action_spawn_a
		|| npc->atk_pattern[npc->atk_pattern_index] == action_spawn_b)
		npc_special_spawn(app, npc_obj, npc);
	if (dist >= npc->vision_range || !npc_has_line_of_sight(app, npc_obj))
	{
		npc->interest--;
		if (npc->interest < 0)
		{
			npc->atk_pattern_index = 0;
			npc->state = state_idle;
			ml_vector3_mul(npc->dir, 0, npc->dir);
			return ;
		}
	}
	else
		npc->interest = npc->max_interest;
	handle_attack_init(app, npc_obj, npc, dist);
	handle_line_of_sight(app, npc_obj, npc, diff);
}

void	npc_update_state(t_doom3d *app, t_3d_object *npc_obj)
{
	t_npc	*npc;
	t_vec3	diff;
	t_vec3	rot;
	float	dist;

	npc = npc_obj->params;
	ml_vector3_copy(npc->dir, rot);
	ml_vector3_sub(npc_obj->aabb.center, app->player.aabb.center, diff);
	dist = ml_vector3_mag(diff);
	if (npc->state == state_idle)
		handle_state_idle(app, npc_obj, npc, dist);
	else if (npc->state == state_attack)
		handle_state_attack(app, npc_obj, npc, diff);
	else if (npc->state == state_atk_anim)
		handle_atk_anim(app, npc_obj);
	if (npc->type != npc_type_elevator && npc->type != npc_type_crate)
		npc_face_player(npc_obj, npc, rot);
}
