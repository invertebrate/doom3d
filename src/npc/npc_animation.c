/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo     <veilo@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2021/02/15 21:41:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** NPC type specific function, each type has their own
*/

void		npc_default_anim_3d_metadata_set(t_anim_metadata *anim_data)
{
	int		i;

	i = -1;
	anim_data->anim_count = 5;
	anim_data->clip_lengths[0] = 1;
	anim_data->clip_lengths[1] = 24;
	anim_data->clip_lengths[2] = 24;
	anim_data->clip_lengths[3] = 24;
	anim_data->clip_lengths[4] = 44;
	anim_data->frame_count = anim_data->clip_lengths[0] + anim_data->clip_lengths[1] +
							anim_data->clip_lengths[2] + anim_data->clip_lengths[3] +
							anim_data->clip_lengths[4];
	anim_data->anim_clip_start_indices[0] = 0;
	anim_data->anim_clip_start_indices[1] = anim_data->clip_lengths[0];
	anim_data->anim_clip_start_indices[2] = anim_data->clip_lengths[0] +
											anim_data->clip_lengths[1];
	anim_data->anim_clip_start_indices[3] = anim_data->clip_lengths[0] +
											anim_data->clip_lengths[1] +
											anim_data->clip_lengths[2];
	anim_data->anim_clip_start_indices[4] = anim_data->clip_lengths[0] +
											anim_data->clip_lengths[1] +
											anim_data->clip_lengths[2] +
											anim_data->clip_lengths[3];
	anim_data->frames_start_idx = 0;//global animation frame array index
	ft_memset(anim_data->anim_frame_numbers,
	0, sizeof(uint32_t) * ANIM_3D_FRAME_MAX);
	while (++i < (int)anim_data->frame_count)
	{
		anim_data->anim_frame_numbers[i] = anim_data->frames_start_idx + i;
	}
}

void		npc_ranged_anim_3d_metadata_set(t_anim_metadata *anim_data)
{
	int		i;
	i = -1;
	anim_data->anim_count = 5;
	anim_data->clip_lengths[0] = 1;
	anim_data->clip_lengths[1] = 59;
	anim_data->clip_lengths[2] = 18;
	anim_data->clip_lengths[3] = 19;
	anim_data->clip_lengths[4] = 28;
	anim_data->frame_count = anim_data->clip_lengths[0] + anim_data->clip_lengths[1] +
							anim_data->clip_lengths[2] + anim_data->clip_lengths[3] +
							anim_data->clip_lengths[4];
	anim_data->frames_start_idx = 117;//global animation frame array index// needs to be hardcoded, cumulative number of all anim frames
	anim_data->anim_clip_start_indices[0] = anim_data->frames_start_idx;
	anim_data->anim_clip_start_indices[1] = anim_data->frames_start_idx + anim_data->clip_lengths[0];
	anim_data->anim_clip_start_indices[2] = anim_data->frames_start_idx + anim_data->clip_lengths[0] +
											anim_data->clip_lengths[1];
	anim_data->anim_clip_start_indices[3] = anim_data->frames_start_idx + anim_data->clip_lengths[0] +
											anim_data->clip_lengths[1] +
											anim_data->clip_lengths[2];
	anim_data->anim_clip_start_indices[4] = anim_data->frames_start_idx + anim_data->clip_lengths[0] +
											anim_data->clip_lengths[1] +
											anim_data->clip_lengths[2] +
											anim_data->clip_lengths[3];
	ft_memset(anim_data->anim_frame_numbers,
	0, sizeof(uint32_t) * ANIM_3D_FRAME_MAX);
	while (++i < (int)anim_data->frame_count)
	{
		anim_data->anim_frame_numbers[i] = anim_data->frames_start_idx + i;
	}
}

void			npc_animation_3d_init(t_doom3d *app, t_3d_object *obj)
{
	t_anim_metadata	anim_data;
	(void)app;
	t_npc			*npc;

	npc = (t_npc*)obj->params;
	if (npc->animation_3d != NULL)
		{
			// ft_printf("freeing anim in npc anim init\n");
			free(npc->animation_3d);
			npc->animation_3d = NULL;
		}
	if (npc->type == npc_type_default)
	{
		npc_default_anim_3d_metadata_set(&anim_data);
	}
	else if (npc->type == npc_type_ranged)
	{
		npc_ranged_anim_3d_metadata_set(&anim_data);
	}
	else
	{
		return ;
	}
	npc_animation_3d_set(app, obj, npc, &anim_data);
}

static void			npc_anim_3d_frames_set(t_doom3d *app, t_3d_object *obj, t_npc *npc)
{
	int			i;

	i = -1;
	while (++i < ANIM_3D_FRAME_MAX)
	{
		npc->animation_3d->animation_frames[i] = NULL;
	}
	i = npc->animation_3d->frames_start_idx - 1;
	while (++i < (int)(npc->animation_3d->frames_start_idx + (npc->animation_3d->frame_count)))
	{
		npc->animation_3d->animation_frames[i] = l3d_object_instantiate(
		hash_map_get(app->active_scene->animation_3d_frames,
			(int64_t)(app->active_scene->asset_files.animation_3d_files[i])), app->unit_size);
		//ToDo: Make material copy if needed
		npc->animation_3d->animation_frames[i]->material->texture =
			obj->material->texture;
		npc->animation_3d->animation_frames[i]->material->shading_opts =
			obj->material->shading_opts;
		l3d_3d_object_scale(npc->animation_3d->animation_frames[i],
							npc->model_scale, npc->model_scale, npc->model_scale);
		l3d_3d_object_rotate(npc->animation_3d->animation_frames[i], 0, 180, 180);//
	}

}

static void			npc_animation_3d_data_copy(t_npc *npc, t_anim_metadata *anim_data)
{
	int		i;

	i = anim_data->frames_start_idx -1;
	npc->animation_3d->frame_count = anim_data->frame_count;
	while (++i <(int)anim_data->frame_count)
	{
		npc->animation_3d->clip_info->anim_frame_numbers[i] =
			anim_data->anim_frame_numbers[i];
		ml_vector3_copy((t_vec3){0.0, 0.0, 0.0},
			npc->animation_3d->frame_object_prev_translation[i]);
	}
	i = -1;
	while (++i < (int)anim_data->anim_count)
	{
		npc->animation_3d->clip_info[i].clip_length = anim_data->clip_lengths[i];
		npc->animation_3d->anim_clip_start_indices[i] = anim_data->anim_clip_start_indices[i];
	}
	npc->animation_3d->anim_count = anim_data->anim_count;
	npc->animation_3d->frames_start_idx = anim_data->frames_start_idx;
}

void				npc_animation_3d_set(t_doom3d *app, t_3d_object *obj, t_npc *npc,
								t_anim_metadata *anim_data)
{
	static int c = 0;//only for animation showcasing
	t_animation_3d	*anim;

	error_check(!(npc->animation_3d = (t_animation_3d*)ft_calloc(sizeof(t_animation_3d))),
		"Failed to malloc for npc animation in npc_animation_set.");
	npc_animation_3d_data_copy(npc, anim_data);
	anim = npc->animation_3d;
	npc->animation_3d->base_object = obj;
	npc_anim_3d_frames_set(app, obj, npc);
	c = c % 4;//only for animation showcasing
	npc->animation_3d->current_clip = anim_3d_type_idle;
	c++;//
	anim->current_object = obj;
	anim->start_frame =
		anim->anim_clip_start_indices[
			(anim->current_clip) % ANIM_3D_TYPE_MOD];
	anim->current_frame =
		anim->anim_clip_start_indices[
			((anim->current_clip) % ANIM_3D_TYPE_MOD)];
	anim->tick_at_update = app->current_tick;
}