/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:21:49 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/02 16:39:35 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_update(t_list *npc)
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
		if (dist >= tmp->app->unit_size * 10)
			tmp->state = state_idle;
		else
		{
			ml_vector3_normalize(diff, tmp->dir);
			ml_vector3_mul(tmp->dir, tmp->speed, tmp->dir);
		}
	}
}