/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2020/12/30 20:32:36 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** NPC type specific function, each type has their own
*/

void		npc_default_anim_metadata_set(t_anim_metadata *anim_data)
{
	anim_data->frame_count = 6;
	anim_data->anim_count = 1;
	anim_data->frames_start_idx = 0;
	ft_memset(anim_data->anim_frame_numbers,
	0, sizeof(uint32_t) * ANIM_3D_FRAME_MAX);
	anim_data->anim_frame_numbers[0] = 0;
}

void			npc_animation_init(t_doom3d *app, t_3d_object *obj)
{
	t_anim_metadata	anim_data;
	t_npc			*npc;

	npc = (t_npc*)obj->params;
	npc->animation->base_object = obj;
	if (npc->type == npc_type_default)
	{
		npc_default_anim_metadata_set(&anim_data);
	}
		npc_animation_set(app, obj, npc, &anim_data);
}

static void			npc_anim_frames_set(t_doom3d *app, t_3d_object *obj, t_npc *npc)
{
	int		i;

	i = npc->animation->frames_start_idx - 1;
	while (++i < (int)(npc->animation->frames_start_idx + (npc->animation->frame_count)))
	{
		npc->animation->animation_frames[i] = l3d_object_instantiate(
		hash_map_get(app->active_scene->anim_frames,
			(int64_t)(app->active_scene->asset_files.animation_files[i])), app->unit_size);
		npc->animation->animation_frames[i]->material = obj->material;
	}
}

static void			npc_animation_data_copy(t_npc *npc, t_anim_metadata *anim_data)
{
	int		i;

	i = -1;
	npc->animation->frame_count = anim_data->frame_count;
	while (++i < (int)anim_data->anim_count)
	{
		npc->animation->anim_frame_numbers[i] =
			anim_data->anim_frame_numbers[i];
	}
	npc->animation->anim_count = anim_data->anim_count;
	npc->animation->frames_start_idx = anim_data->frames_start_idx;
}

void				npc_animation_set(t_doom3d *app, t_3d_object *obj, t_npc *npc,
								t_anim_metadata *anim_data)
{
	error_check(!(npc->animation = (t_animation*)ft_calloc(sizeof(t_animation))),
		"Failed to malloc for npc animation in npc_animation_set.");
	npc_animation_data_copy(npc, anim_data);
	npc_anim_frames_set(app, obj, npc);
}