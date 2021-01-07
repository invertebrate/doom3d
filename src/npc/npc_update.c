/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:21:49 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/06 16:12:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_atk_anim(t_doom3d *app, t_3d_object *npc_obj)
{
	uint32_t		new_time;
	t_npc			*npc;

	(void)app; //!ToDo: Remove from params if app is never needed...
	npc = npc_obj->params;
	new_time = SDL_GetTicks();
	npc->atk_timer += new_time - npc->atk_start;
	if (npc->atk_timer > npc->atk_dur)
	{
		ft_printf("npc %d attacked!\n", npc_obj->id);//test
		npc->state = state_attack;
	}
}

void		npc_update(t_doom3d *app, t_3d_object *npc_obj)
{
	t_npc	*npc;
	t_vec3	diff;
	float	dist;

	npc = npc_obj->params;
	ml_vector3_sub(npc_obj->position, app->player.pos, diff);
	dist = ml_vector3_mag(diff);
	if (npc->state == state_idle)
	{
		//ft_printf("state of npc %d is idle, at dist = |%f|\n", tmp->id, dist);//test
		if (dist < app->unit_size * 10)
			npc->state = state_attack;
		else
			ml_vector3_mul(npc->dir, 0, npc->dir);
	}
	else if (npc->state == state_attack)
	{
		//ft_printf("state of npc %d is attack, at dist = |%f|\n", tmp->id, dist);//test
		if (dist >= npc->vision_range)
			npc->state = state_idle;
		else if (dist < npc->atk_range)
		{
			npc->atk_timer = 0;
			npc->atk_start = SDL_GetTicks();
			npc->state = state_atk_anim;
		}
		else
		{
			ml_vector3_normalize(diff, npc->dir);
			ml_vector3_mul(npc->dir, npc->speed, npc->dir);
		}
	}
	else if (npc->state == state_atk_anim)
	{
		handle_atk_anim(app, npc_obj);
	}
}