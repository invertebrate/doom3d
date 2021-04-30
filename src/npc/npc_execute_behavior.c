/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_execute_behavior.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:22:03 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/30 20:06:13 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_state_attack(t_doom3d *app, t_3d_object *npc_obj,
															t_npc *npc)
{
	t_vec3	dist;

	if (npc_has_line_of_sight(app, npc_obj) == false)
		npc_move_step_to_waypoint(app, npc_obj);
	else if (npc->advance == true)
	{
		ml_vector3_sub(npc_obj->position, app->player.pos, dist);
		if (ml_vector3_mag(dist) > npc->atk_range / 2)
		{
			if (npc->animation_3d &&
				npc->animation_3d->current_clip != anim_3d_type_move)
				anim_3d_clip_loop(app, npc_obj, anim_3d_type_move, 0);
			l3d_3d_object_translate(npc_obj, npc->dir[0], 0, npc->dir[2]);
			l3d_object_aabb_update(npc_obj);
		}
	}
}

void		npc_execute_behavior(t_doom3d *app, t_3d_object *npc_obj)
{
	t_npc	*npc;

	if (npc_obj == NULL || npc_obj->params == NULL)
		return ;
	npc = npc_obj->params;
	if (npc->state == state_idle)
	{
		if (npc->num_patrol_path_nodes != 0)
			npc_move_step_to_waypoint(app, npc_obj);
		else if (npc->animation_3d &&
					npc->animation_3d->current_clip != anim_3d_type_idle)
			anim_3d_clip_loop(app, npc_obj, anim_3d_type_idle, 0);
	}
	else if (npc->state == state_attack)
		handle_state_attack(app, npc_obj, npc);
}
