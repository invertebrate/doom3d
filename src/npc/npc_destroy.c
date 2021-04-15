/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:32:11 by veilo             #+#    #+#             */
/*   Updated: 2021/04/14 23:49:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool		animation_3d_destroy(t_animation_3d *anim)
{
	uint32_t	i;

	if (anim == NULL)
		return (false);
	i = 0;
	while (i < ANIM_3D_FRAME_MAX)
	{
		if (anim->animation_frames[i] != NULL)
		{
			l3d_3d_object_destroy(anim->animation_frames[i]);
			anim->animation_frames[i] = NULL;
		}
		i++;
	}
	free(anim);
	anim = NULL;
	return (true);
}

t_bool				npc_destroy(t_3d_object *npc_obj)
{	
	if (npc_obj == NULL || npc_obj->type != object_type_npc)
		return (false);
	if (((t_npc*)npc_obj->params)->type == npc_type_default ||
		((t_npc*)npc_obj->params)->type == npc_type_ranged)
	{
		if (!animation_3d_destroy((((t_npc*)npc_obj->params))->animation_3d))
			LOG_WARN("Failed to delete animation frames (NULL)");
	}
	l3d_3d_object_destroy(npc_obj);
	return (true);
}