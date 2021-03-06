/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:21:49 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/04 17:20:38 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		npc_shoot_projectile(t_doom3d *app, t_vec3 origin, t_vec3 dir)
{
	t_projectile	projectile;
	t_vec3			rot;
	t_vec3			add;
	t_vec3			neworigin;
	t_vec3			newdir;

	ft_memset(&projectile, 0, sizeof(t_projectile));
	ft_memcpy(&projectile,
		&app->projectile_data[projectile_type_rpg],
		sizeof(t_projectile));
	rot[0] = 0; //todo - proper angles if not replacing with fireball projectile
	rot[1] = 0; 
	rot[2] = 0;
	ml_vector3_copy(rot, projectile.euler_angles);
	ml_vector3_normalize(dir, newdir);
	ml_vector3_copy(newdir, projectile.dir);
	ml_vector3_mul(newdir, app->unit_size * 10, add);
	ml_vector3_add(origin, add, neworigin);
	place_projectile_object_in_scene(app, &projectile, neworigin, rot);
}

static void	handle_atk_anim(t_doom3d *app, t_3d_object *npc_obj)
{
	uint32_t		new_time;
	t_npc			*npc;
	t_vec3			dist;

	(void)app; //!ToDo: Remove from params if app is never needed...
	npc = npc_obj->params;
	new_time = SDL_GetTicks();
	npc->atk_timer += new_time - npc->atk_start;
	if (npc->atk_timer > npc->atk_dur)
	{
		// ft_printf("atk pattern = %d, at index %d\n", npc->atk_pattern[npc->atk_pattern_index], npc->atk_pattern_index);//test
		if (npc->atk_pattern[npc->atk_pattern_index] == action_melee_basic)
		{
			// ft_printf("npc %d attacked!\n", npc_obj->id);//test
			ml_vector3_sub(app->player.pos, npc_obj->position, dist);
			if (ml_vector3_mag(dist) < npc->atk_range)
				player_onhit(app, npc->atk_dmg);
		}
		if (npc->atk_pattern[npc->atk_pattern_index] == action_projectile_rpg)
		{
			// ft_printf("npc %d shot a rocket!\n", npc_obj->id);//test
			npc_shoot_projectile(app, npc_obj->position, npc->dir);
		}
		npc->state = state_attack;
	}
}

void		npc_update_state(t_doom3d *app, t_3d_object *npc_obj)
{
	t_npc	*npc;
	t_vec3	diff;
	float	dist;

	npc = npc_obj->params;
	ml_vector3_sub(npc_obj->position, app->player.pos, diff);
	dist = ml_vector3_mag(diff);
	if (npc->state == state_idle)
	{
		if (dist < npc->vision_range &&
			npc_has_line_of_sight(app, npc_obj))
			npc->state = state_attack;
		npc_get_dir_to_next_waypoint(app, npc_obj);
	}
	else if (npc->state == state_attack)
	{
		npc->atk_pattern_index++;
		if (npc->atk_pattern[npc->atk_pattern_index] == action_repeat)
			npc->atk_pattern_index = 0;
		if (dist >= npc->vision_range || !npc_has_line_of_sight(app, npc_obj))
		{
			npc->interest--;
			//ft_printf("npc %d interest = %d\n", npc_obj->id, npc->interest);//test
			if (npc->interest < 0)
			{
				npc->atk_pattern_index = 0;
				npc->state = state_idle;
			}
		}
		else
			npc->interest = npc->max_interest;
		if (dist < npc->atk_range 
		&& npc->atk_pattern[npc->atk_pattern_index] == action_melee_basic)
		{
			npc->atk_timer = 0;
			npc->atk_start = SDL_GetTicks();
			npc->state = state_atk_anim;
		}
		if (npc->atk_pattern[npc->atk_pattern_index] == action_projectile_rpg &&
			npc_has_line_of_sight(app, npc_obj))
		{
			npc->atk_timer = 0;
			npc->atk_start = SDL_GetTicks();
			npc->state = state_atk_anim;
		}
		ml_vector3_normalize(diff, npc->dir);
		ml_vector3_mul(npc->dir, -npc->speed, npc->dir);
	}
	else if (npc->state == state_atk_anim)
	{
		handle_atk_anim(app, npc_obj);
	}
}