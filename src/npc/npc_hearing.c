/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_hearing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:08:28 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/29 17:58:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** check if npc can hear a loud sound originating from src, eg. gunshot landing
*/

void	check_npc_hearing(t_doom3d *app, t_vec3 src)
{
	int			i;
	t_3d_object	*obj;
	t_npc		*npc;
	t_vec3		dist;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		if (obj->type != object_type_npc)
			continue ;
		npc = (t_npc *)obj->params;
		if (npc->state == state_death_anim)
			return ;
		ml_vector3_sub(src, obj->position, dist);
		if (ml_vector3_mag(dist) < npc->hearing_range
			&& npc->type != npc_type_elevator)
		{
			npc->state = state_attack;
			npc->interest = npc->max_interest;
		}
	}
}
