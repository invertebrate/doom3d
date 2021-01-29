/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2021/01/29 20:26:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** NPC type specific function, each type has their own
*/

void		npc_default_anim_3d_metadata_set(t_anim_metadata *anim_data)
{
	anim_data->frame_count = 6;
	anim_data->anim_count = 1;
	anim_data->frames_start_idx = 0;
	ft_memset(anim_data->anim_frame_numbers,
	0, sizeof(uint32_t) * ANIM_3D_FRAME_MAX);
	anim_data->anim_frame_numbers[0] = 0;
}

void			npc_animation_3d_init(t_doom3d *app, t_3d_object *obj)
{
	t_anim_metadata	anim_data;
	t_npc			*npc;

	npc = (t_npc*)obj->params;
	if (npc->type == npc_type_default)
	{
		npc_default_anim_3d_metadata_set(&anim_data);
	}
	npc_animation_3d_set(app, obj, npc, &anim_data);
}

static void			npc_anim_3d_frames_set(t_doom3d *app, t_3d_object *obj, t_npc *npc)
{
	int		i;

	i = npc->animation_3d->frames_start_idx - 1;
	while (++i < (int)(npc->animation_3d->frames_start_idx + (npc->animation_3d->frame_count)))
	{
		npc->animation_3d->animation_frames[i] = l3d_object_instantiate(
		hash_map_get(app->active_scene->animation_3d_frames,
			(int64_t)(app->active_scene->asset_files.animation_3d_files[i])), app->unit_size);
		npc->animation_3d->animation_frames[i]->material = obj->material;
	}
}

static void			npc_animation_3d_data_copy(t_npc *npc, t_anim_metadata *anim_data)
{
	int		i;

	i = -1;
	npc->animation_3d->frame_count = anim_data->frame_count;
	while (++i < (int)anim_data->anim_count)
	{
		npc->animation_3d->anim_frame_numbers[i] =
			anim_data->anim_frame_numbers[i];
	}
	npc->animation_3d->anim_count = anim_data->anim_count;
	npc->animation_3d->frames_start_idx = anim_data->frames_start_idx;
}

void				npc_animation_3d_set(t_doom3d *app, t_3d_object *obj, t_npc *npc,
								t_anim_metadata *anim_data)
{
	error_check(!(npc->animation_3d = (t_animation_3d*)ft_calloc(sizeof(t_animation_3d))),
		"Failed to malloc for npc animation in npc_animation_set.");
	npc_animation_3d_data_copy(npc, anim_data);
	npc->animation_3d->base_object = obj;
	npc_anim_3d_frames_set(app, obj, npc);
}