/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:12:44 by veilo             #+#    #+#             */
/*   Updated: 2021/04/29 18:30:23 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

uint32_t			arr_sum(uint32_t *arr, uint32_t length)
{
	uint32_t	i;
	uint32_t	result;

	result = 0;
	i = -1;
	while (++i < length)
	{
		result += arr[i];
	}
	return (result);
}

void				npc_anim3d_material_copy(t_3d_object *source,
												t_3d_object *dest)
{
	int		i;

	i = -1;
	dest->material->texture = source->material->texture;
	dest->material->shading_opts = e_shading_standard;
	dest->material->normal_map = source->material->normal_map;
	dest->material->num_lights = source->material->num_lights;
	dest->material->flashlight = source->material->flashlight;
	while (++i < L3D_MAX_LIGHTS)
		dest->material->light_sources[i] = source->material->light_sources[i];
}

void				init_anim_instance(t_doom3d *app,
										t_anim_3d_instance *anim_instance)
{
	anim_instance->app = app;
	anim_instance->active = false;
	anim_instance->anim_clip = 0;
	anim_instance->f_event = NULL;
	anim_instance->start_frame = 0;
	anim_instance->trigger_time = 0.0;
	anim_instance->event_triggered = false;
	anim_instance->params[0] = NULL;
	anim_instance->params[1] = NULL;
	anim_instance->params[2] = NULL;
}

void				npc_animation_3d_data_copy(t_npc *npc,
												t_anim_metadata *anim_data)
{
	int		i;
	t_mat4	id_matrix;

	ml_matrix4_id(id_matrix);
	i = anim_data->frames_start_idx - 1;
	npc->animation_3d->frame_count = anim_data->frame_count;
	while (++i < (int)anim_data->frame_count)
	{
		npc->animation_3d->clip_info->anim_frame_numbers[i] =
			anim_data->anim_frame_numbers[i];
		ml_vector3_copy((t_vec3){0.0, 0.0, 0.0},
			npc->animation_3d->frame_object_prev_translation[i]);
		ml_matrix4_copy(id_matrix,
			npc->animation_3d->frame_object_prev_rotation[i]);
	}
	i = -1;
	while (++i < (int)anim_data->anim_count)
	{
		npc->animation_3d->clip_info[i].clip_length =
			anim_data->clip_lengths[i];
		npc->animation_3d->anim_clip_start_indices[i] =
			anim_data->anim_clip_start_indices[i];
	}
	npc->animation_3d->anim_count = anim_data->anim_count;
	npc->animation_3d->frames_start_idx = anim_data->frames_start_idx;
}
