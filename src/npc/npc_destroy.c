/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:03:02 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/23 18:03:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	animation_destroy(t_animation *animation)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)animation->frame_count)
	{
		l3d_3d_object_destroy(animation->animation_frames[i]);
	}
	free(animation);
	animation = NULL;
}

void		npc_object_destroy(t_3d_object *npc_object)
{
	t_npc 	*npc;

	if (npc_object->type == object_type_npc)
	{
		npc = npc_object->params;
		if (npc->animation)
			animation_destroy(npc->animation);
		l3d_3d_object_destroy(npc_object);
	}
}