/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2021/04/05 18:15:26 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void					update_app_ticks(t_doom3d *app)
{
	app->current_tick = (SDL_GetPerformanceCounter() * TICKS_PER_SEC) /
						SDL_GetPerformanceFrequency();
}

void		npc_anim_3d_position_update(t_3d_object *obj)
{
	t_animation_3d		*anim;

	anim = NULL;
	if (obj->type == object_type_npc && ((t_npc*)obj->params)->animation_3d != NULL)
		anim = ((t_npc*)obj->params)->animation_3d;
	else
		return ;
	l3d_3d_object_translate(anim->current_object,
							-anim->frame_object_prev_translation[anim->frames_start_idx + anim->current_frame][0],
							-anim->frame_object_prev_translation[anim->frames_start_idx + anim->current_frame][1],
							-anim->frame_object_prev_translation[anim->frames_start_idx + anim->current_frame][2]);
	ml_vector3_copy(obj->position, anim->current_object->position);
	l3d_3d_object_translate(anim->current_object, obj->position[0],
							obj->position[1], obj->position[2]);
	ml_vector3_copy((t_vec3){obj->position[0], obj->position[1], obj->position[2]},
						anim->frame_object_prev_translation[anim->frames_start_idx + anim->current_frame]);
}

uint32_t				anim_3d_frame_update(t_doom3d *app, t_animation_3d *animation)
{
	uint32_t	current_frame;

	if (animation->current_clip == anim_3d_type_null)
	{
		npc_anim_3d_position_update(animation->base_object);
		return (UINT32_MAX);
	}
	if (((app->current_tick - animation->tick_at_update) % (TICKS_PER_SEC)) > (TICKS_PER_SEC / ANIM_3D_FPS))
	{
		animation->current_frame++;
		if (animation->current_frame > animation->clip_info[animation->current_clip % ANIM_3D_TYPE_MOD].clip_length +
				animation->anim_clip_start_indices[animation->current_clip % ANIM_3D_TYPE_MOD] - 1)
			animation->current_frame = animation->anim_clip_start_indices[animation->current_clip % ANIM_3D_TYPE_MOD];
		animation->tick_at_update = app->current_tick;
	}
	current_frame = animation->current_frame;
	animation->current_object = animation->animation_frames[animation->current_frame];
	npc_anim_3d_position_update(animation->base_object);
	// npc_anim_3d_rotation_update(animation->base_object);
	return (current_frame);
}

/*
**	Changes the current playing animation clip of an object
*/

void					anim_3d_clip_set(t_doom3d *app, t_3d_object *obj,
										t_animation_3d_type clip, uint32_t start_frame)
{
	t_animation_3d		*anim;

	if (!(obj->type == object_type_npc && ((t_npc*)obj->params)->animation_3d != NULL))
	{
		LOG_ERROR("Tried to set animation clip to an object with no animation_3d");
		return ;
	}
	anim = ((t_npc*)obj->params)->animation_3d;
	anim->current_clip = clip;
	anim->current_frame = start_frame;
	anim->current_object = anim->animation_frames[anim->anim_clip_start_indices[clip %
													ANIM_3D_TYPE_MOD]];
	anim->tick_at_update = app->current_tick;
	npc_anim_3d_position_update(obj);
}
