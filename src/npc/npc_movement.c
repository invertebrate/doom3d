/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:49:44 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/23 18:28:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			npc_translate(t_3d_object *npc_obj, float x, float y, float z)
{
	t_npc	*npc;
	int32_t	i;

	if (npc_obj->type == object_type_npc)
	{
		npc = npc_obj->params;
		if (npc->animation)
		{
			i = -1;
			while (++i < (int32_t)npc->animation->frame_count)
			{
				l3d_3d_object_translate(npc->animation->animation_frames[i],
					x, y, z);
			}
		}
		l3d_3d_object_translate(npc_obj, x, y, z);	
	}
}

void			npc_rotate(t_3d_object *npc_obj, float x, float y, float z)
{
	t_npc	*npc;
	int32_t	i;

	if (npc_obj->type == object_type_npc)
	{
		npc = npc_obj->params;
		if (npc->animation)
		{
			i = -1;
			while (++i < (int32_t)npc->animation->frame_count)
			{
				l3d_3d_object_rotate(npc->animation->animation_frames[i],
					x, y, z);
			}
		}
		l3d_3d_object_rotate(npc_obj, x, y, z);	
	}
}
