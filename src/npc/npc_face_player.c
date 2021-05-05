/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_face_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:18:00 by phakakos          #+#    #+#             */
/*   Updated: 2021/05/05 14:18:02 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_face_player(t_3d_object *npc_obj, t_npc *npc, t_vec3 start)
{
	t_vec3	curr;
	float	sangle;
	float	cangle;

	ml_vector3_copy(npc->dir, curr);
	if (start[0] == curr[0] && start[1] == curr[1] && start[2] == curr[2])
		return ;
	sangle = atan2(start[2] / 120, start[0] / 120) * 180 / 3.14f;
	cangle = atan2(curr[2] / 120, curr[0] / 120) * 180 / 3.14f;
	l3d_3d_object_rotate(npc_obj, 0, cangle - sangle, 0);
}
