/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_move_to_waypoint.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:07:07 by ahakanen          #+#    #+#             */
/*   Updated: 2021/02/16 18:26:53 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_get_dir_to_next_waypoint(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*npc;
	t_vec3	diff;

	npc = obj->params;
	if (npc->patrol_path[0] == NULL)
		return ;
	if (npc->patrol_path[npc->patrol_path_index] == NULL)
		npc->patrol_path_index = 0;
	if (npc->patrol_path_index != -1)
	{
		ml_vector3_sub(obj->position,
					npc->patrol_path[npc->patrol_path_index]->position, diff);
		ml_vector3_normalize(diff, npc->dir);
		ml_vector3_mul(npc->dir, -npc->speed, npc->dir);
	}
	if (ml_vector3_mag(diff) < app->unit_size * 1.5)
	{
		npc->patrol_path_index++;
		if (npc->type == npc_type_elevator)
			npc->speed = 0;
	}
	// ft_printf("object id %d dir set to {%f, %f, %f}\n", obj->id, npc->dir[0], npc->dir[1], npc->dir[2]); //test
	// ft_printf("object id %d patrol_path_index is %d\n", obj->id, npc->patrol_path_index); //test
	// ft_printf("object id %d is patrolling at {%f, %f, %f}\n", obj->id, obj->position[0], obj->position[1], obj->position[2]); //test
}

void	npc_move_step_to_waypoint(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*npc;

	(void)app; //delete this later
	npc = obj->params;
	if (npc->is_flying)
		l3d_3d_object_translate(obj, npc->dir[0], npc->dir[1], npc->dir[2]);
	else
		l3d_3d_object_translate(obj, npc->dir[0], 0, npc->dir[2]);
}