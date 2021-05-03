/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_move_to_waypoint.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:07:07 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/03 17:46:27 by sotamursu        ###   ########.fr       */
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
	reset_patrol_path_if_needed(npc);
	if (npc->type != npc_type_elevator && !npc->attack_path[0])
		npc_find_path(app, npc, obj->position,
			npc->patrol_path[npc->patrol_path_index]->position);
	if (npc->type != npc_type_elevator && npc_get_dir_to_next_atk(app, obj))
		npc->patrol_path_index++;
	else
	{
		if (npc->patrol_path_index != -1)
		{
			ml_vector3_sub(obj->position,
				npc->patrol_path[npc->patrol_path_index]->position, diff);
			ml_vector3_normalize(diff, npc->dir);
			ml_vector3_mul(npc->dir, -npc->speed, npc->dir);
		}
		handle_reaching_waypoint(app, npc, diff);
	}
}

t_bool	npc_get_dir_to_next_atk(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*npc;
	t_vec3	diff;

	npc = obj->params;
	if (npc->attack_path[0] == NULL
		|| npc->attack_path[npc->attack_path_index] == NULL)
	{
		npc->attack_path_index = 0;
		ft_memset(npc->attack_path, 0, sizeof(t_3d_object *)
			* MAX_PATH_NODE_NETWORK_SIZE);
		return (true);
	}
	ml_vector3_sub(obj->position,
		npc->attack_path[npc->attack_path_index]->position, diff);
	ml_vector3_normalize(diff, npc->dir);
	ml_vector3_mul(npc->dir, -npc->speed, npc->dir);
	if (ml_vector3_mag(diff) < app->unit_size * 1.5)
		npc->attack_path_index++;
	return (false);
}

void	npc_move_step_to_waypoint(t_doom3d *app, t_3d_object *obj)
{
	t_npc	*npc;

	(void)app;
	npc = obj->params;
	if (obj->params_type == npc_type_elevator)
	{
		l3d_3d_object_translate(obj, npc->dir[0], npc->dir[1], npc->dir[2]);
		l3d_object_aabb_update(obj);
	}
	else
	{
		if (npc->animation_3d
			&& npc->animation_3d->current_clip != anim_3d_type_move)
			anim_3d_clip_loop(app, obj, anim_3d_type_move, 0);
		l3d_3d_object_translate(obj, npc->dir[0], 0, npc->dir[2]);
		l3d_object_aabb_update(obj);
	}
}
