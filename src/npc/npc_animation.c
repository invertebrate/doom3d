/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2021/04/29 17:59:10 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** NPC type specific function, each type has their own
*/

void		npc_monster01_anim_3d_metadata_set(t_anim_metadata *anim_data)
{
	int		i;

	i = -1;
	anim_data->anim_count = 5;
	anim_data->clip_lengths[0] = 1;
	anim_data->clip_lengths[1] = 65;
	anim_data->clip_lengths[2] = 13;
	anim_data->clip_lengths[3] = 17;
	anim_data->clip_lengths[4] = 49;
	anim_data->frame_count = arr_sum(anim_data->clip_lengths,
										anim_data->anim_count);
	anim_data->anim_clip_start_indices[0] = 0;
	anim_data->anim_clip_start_indices[1] = anim_data->clip_lengths[0];
	anim_data->anim_clip_start_indices[2] = arr_sum(anim_data->clip_lengths, 2);
	anim_data->anim_clip_start_indices[3] = arr_sum(anim_data->clip_lengths, 3);
	anim_data->anim_clip_start_indices[4] = arr_sum(anim_data->clip_lengths, 4);
	anim_data->frames_start_idx = 0;
	ft_memset(anim_data->anim_frame_numbers,
	0, sizeof(uint32_t) * ANIM_3D_FRAME_MAX);
	while (++i < (int)anim_data->frame_count)
	{
		anim_data->anim_frame_numbers[i] = anim_data->frames_start_idx + i;
	}
}

void		npc_monster02_anim_3d_metadata_set(t_anim_metadata *anim_data)
{
	int		i;
	i = -1;
	anim_data->anim_count = 5;
	anim_data->clip_lengths[0] = 1;
	anim_data->clip_lengths[1] = 59;
	anim_data->clip_lengths[2] = 20;
	anim_data->clip_lengths[3] = 12;
	anim_data->clip_lengths[4] = 32;
	anim_data->frame_count = arr_sum(anim_data->clip_lengths,
										anim_data->anim_count);
	anim_data->frames_start_idx = 145;
	anim_data->anim_clip_start_indices[0] = anim_data->frames_start_idx;
	anim_data->anim_clip_start_indices[1] = anim_data->frames_start_idx +
											anim_data->clip_lengths[0];
	anim_data->anim_clip_start_indices[2] = anim_data->frames_start_idx +
											arr_sum(anim_data->clip_lengths, 2);
	anim_data->anim_clip_start_indices[3] = anim_data->frames_start_idx +
											arr_sum(anim_data->clip_lengths, 3);
	anim_data->anim_clip_start_indices[4] = anim_data->frames_start_idx +
											arr_sum(anim_data->clip_lengths, 4);
	ft_memset(anim_data->anim_frame_numbers,
		0, sizeof(uint32_t) * ANIM_3D_FRAME_MAX);
	while (++i < (int)anim_data->frame_count)
		anim_data->anim_frame_numbers[i] = anim_data->frames_start_idx + i;
}

void			npc_animation_3d_init(t_doom3d *app, t_3d_object *obj)
{
	t_anim_metadata	anim_data;
	t_npc			*npc;

	npc = (t_npc*)obj->params;
	if (npc->animation_3d != NULL)
		{
			free(npc->animation_3d);
			npc->animation_3d = NULL;
		}
	if (npc->type == npc_type_monster01 || npc->type == npc_type_monster01_a ||
		npc->type == npc_type_monster01_range)
		npc_monster01_anim_3d_metadata_set(&anim_data);
	else if (npc->type == npc_type_monster02)
		npc_monster02_anim_3d_metadata_set(&anim_data);
	else
		return ;
	npc_animation_3d_set(app, obj, npc, &anim_data);
}


static void			npc_anim_3d_frames_set(t_doom3d *app, t_3d_object *obj,
											t_npc *npc)
{
	int			i;

	i = -1;
	while (++i < ANIM_3D_FRAME_MAX)
	{
		npc->animation_3d->animation_frames[i] = NULL;
	}
	i = npc->animation_3d->frames_start_idx - 1;
	while (++i < (int)(npc->animation_3d->frames_start_idx +
			(npc->animation_3d->frame_count)))
	{
		npc->animation_3d->animation_frames[i] = l3d_object_instantiate(
		hash_map_get(app->active_scene->animation_3d_frames,
			(int64_t)(app->active_scene->asset_files.animation_3d_files[i])),
			app->unit_size);
		npc->animation_3d->animation_frames[i]->material->shading_opts = 0;
		npc_anim3d_material_copy(obj, npc->animation_3d->animation_frames[i]);
		l3d_3d_object_scale(npc->animation_3d->animation_frames[i],
							npc->model_scale, npc->model_scale,
							npc->model_scale);
		l3d_3d_object_rotate(npc->animation_3d->animation_frames[i],
							0, 180, 180);
		ml_matrix4_id(npc->animation_3d->frame_object_prev_rotation[i]);
	}
}

void				npc_animation_3d_set(t_doom3d *app, t_3d_object *obj,
										t_npc *npc, t_anim_metadata *anim_data)
{
	t_animation_3d	*anim;

	error_check(!(npc->animation_3d = (t_animation_3d*)ft_calloc(
										sizeof(t_animation_3d))),
		"Failed to malloc for npc animation in npc_animation_set.");
	error_check(!(npc->animation_3d->current_anim_instance =
		(t_anim_3d_instance*)ft_calloc(sizeof(t_anim_3d_instance))),
		"Failed to malloc for npc animation_instance in npc_animation_set.");
	init_anim_instance(app, npc->animation_3d->current_anim_instance);
	npc_animation_3d_data_copy(npc, anim_data);
	anim = npc->animation_3d;
	npc->animation_3d->base_object = obj;
	npc_anim_3d_frames_set(app, obj, npc);
	npc->animation_3d->current_clip = anim_3d_type_idle;
	anim->current_frame =
		anim->anim_clip_start_indices[
			((anim->current_clip) % ANIM_3D_TYPE_MOD)];
	anim->current_object = anim->animation_frames[anim->current_frame];
	anim->tick_at_update = app->current_tick;
}
