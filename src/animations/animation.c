/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo     <veilo@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2021/04/29 18:39:40 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
**	Updates the animation frames if an instance is active.
*/

uint32_t				anim_3d_instance_update(t_doom3d *app,
												t_animation_3d *animation)
{
	uint32_t	clip_length;
	uint32_t	clip_start_idx;
	float		elapsed_time;

	clip_length = animation->clip_info[animation->current_anim_instance->
					anim_clip % ANIM_3D_TYPE_MOD].clip_length;
	clip_start_idx = animation->anim_clip_start_indices[
			animation->current_anim_instance->anim_clip % ANIM_3D_TYPE_MOD];
	if (frame_time_expired(app, animation))
	{
		animation->current_frame++;
		animation->tick_at_update = app->current_tick;
	}
	elapsed_time = (float)(animation->current_frame - clip_start_idx) /
					((float)clip_length - 1);
	if (!instance_status_check(animation, elapsed_time))
		return (animation->current_frame);
	animation->current_object =
		animation->animation_frames[animation->current_frame];
	if (animation != NULL && animation->base_object != NULL)
	{
		npc_anim_3d_position_update(animation);
		npc_anim_3d_rotation_update(animation);
	}
	else
	{
		LOG_WARN("Tried to update animation instance of an invalid object!");
		return (UINT32_MAX - 1);
	}
	return (animation->current_frame);
}

uint32_t				anim_3d_loop_update(t_doom3d *app,
											t_animation_3d *animation)
{
	if (frame_time_expired(app, animation))
	{
		animation->current_frame++;
		if (anim_3d_clip_ended(animation))
			animation->current_frame =
				animation->anim_clip_start_indices[animation->current_clip
													% ANIM_3D_TYPE_MOD];
		animation->tick_at_update = app->current_tick;
	}
	animation->current_object =
		animation->animation_frames[animation->current_frame];
	if (animation != NULL && animation->base_object != NULL)
	{
		npc_anim_3d_position_update(animation);
		npc_anim_3d_rotation_update(animation);
	}
	else
	{
		LOG_WARN("Tried to update animation clip loop of an invalid object!");
		return (UINT32_MAX - 1);
	}
	return (animation->current_frame);
}

uint32_t				anim_3d_frame_update(t_doom3d *app,
											t_animation_3d *animation)
{
	if (animation == NULL || animation->base_object == NULL)
	{
		return (UINT32_MAX - 1);
	}
	if (animation->current_clip == anim_3d_type_null)
	{
		npc_anim_3d_position_update(animation);
		npc_anim_3d_rotation_update(animation);
		return (UINT32_MAX);
	}
	if (animation->current_anim_instance->active == true)
	{
		return (anim_3d_instance_update(app, animation));
	}
	else
	{
		return (anim_3d_loop_update(app, animation));
	}
}

/*
** Changes the current playing animation clip of an object
*/

uint32_t					anim_3d_clip_loop(t_doom3d *app, t_3d_object *obj,
										t_animation_3d_type clip,
										uint32_t start_frame)
{
	t_animation_3d		*animation;

	if (!(check_obj_3d_anim(obj)))
	{
		LOG_ERROR("Tried to set anim clip to an object with no animation_3d");
		return (UINT32_MAX - 1);
	}
	animation = ((t_npc*)obj->params)->animation_3d;
	animation->current_clip = clip;
	animation->current_frame = animation->anim_clip_start_indices[
								clip % ANIM_3D_TYPE_MOD] + start_frame;
	animation->current_object = animation->animation_frames[
								animation->current_frame];
	animation->tick_at_update = app->current_tick;
	if (animation != NULL && animation->base_object != NULL)
	{
		npc_anim_3d_position_update(animation);
		npc_anim_3d_rotation_update(animation);
	}
	else
	{
		LOG_WARN("Tried to update animation clip loop of an invalid object!");
		return (UINT32_MAX - 1);
	}
	return (animation->current_frame);
}

t_bool					anim_3d_clip_play(t_doom3d *app, t_3d_object *obj,
										t_anim_3d_instance *anim_instance)
{
	t_animation_3d		*anim;

	if (!(check_obj_3d_anim(obj)))
	{
		LOG_ERROR("Tried to play animation clip of "
		"an object with no animation_3d");
		return false;
	}
	else if (anim_instance == NULL || anim_instance->f_event == NULL)
	{
		LOG_ERROR("Tried to play animation clip with invalid instance data");
		return false;
	}
	anim = ((t_npc*)obj->params)->animation_3d;
	copy_instance_data(anim, anim_instance);
	anim->current_frame = anim->anim_clip_start_indices[anim_instance->anim_clip
							% ANIM_3D_TYPE_MOD] + anim_instance->start_frame;
	anim->current_anim_instance->active = true;
	anim->current_object = anim->animation_frames[anim->current_frame];
	anim->tick_at_update = app->current_tick;
	npc_anim_3d_position_update(anim);
	npc_anim_3d_rotation_update(anim);
	return (true);
}
