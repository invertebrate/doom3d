/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:21:49 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/05 19:43:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_atk_anim(t_npc *npc)
{
	uint32_t		new_time;

	new_time = SDL_GetTicks();
	npc->atk_timer += new_time - npc->atk_start;
	if (npc->atk_timer > npc->atk_dur)
	{
		ft_printf("npc %d attacked!\n", npc->id);//test
		npc->state = state_attack;
	}
}

void		npc_update(t_list *npc)
{
	t_npc	*tmp;
	t_vec3	diff;
	float	dist;

	tmp = npc->content;
	ml_vector3_sub(tmp->pos, tmp->app->player.pos, diff);
	dist = ml_vector3_mag(diff);
	if (tmp->state == state_idle)
	{
		//ft_printf("state of npc %d is idle, at dist = |%f|\n", tmp->id, dist);//test
		if (dist < tmp->app->unit_size * 10)
			tmp->state = state_attack;
		else
			ml_vector3_mul(tmp->dir, 0, tmp->dir);
	}
	else if (tmp->state == state_attack)
	{
		//ft_printf("state of npc %d is attack, at dist = |%f|\n", tmp->id, dist);//test
		if (dist >= tmp->vision_range)
			tmp->state = state_idle;
		else if (dist < tmp->atk_range)
		{
			tmp->atk_timer = 0;
			tmp->atk_start = SDL_GetTicks();
			tmp->state = state_atk_anim;
		}
		else
		{
			ml_vector3_normalize(diff, tmp->dir);
			ml_vector3_mul(tmp->dir, tmp->speed, tmp->dir);
		}
	}
	else if (tmp->state == state_atk_anim)
	{
		handle_atk_anim(tmp);
	}
}