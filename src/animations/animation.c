/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2021/04/18 20:43:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void					update_app_ticks(t_doom3d *app)
{
	app->current_tick = (SDL_GetPerformanceCounter() * TICKS_PER_SEC) /
						SDL_GetPerformanceFrequency();
}

/*
**	Updates the npc position to current animation frame
*/

void		npc_anim_3d_position_update(t_animation_3d *anim)
{
	if (anim == NULL || anim->current_object == NULL || anim->base_object == NULL)
	{
		return ;
	}
	l3d_3d_object_translate(anim->current_object,
				-anim->frame_object_prev_translation[anim->frames_start_idx +
					anim->current_frame][0],
				-anim->frame_object_prev_translation[anim->frames_start_idx +
					anim->current_frame][1],
				-anim->frame_object_prev_translation[anim->frames_start_idx +
					anim->current_frame][2]);
	l3d_3d_object_translate(anim->current_object,
							anim->base_object->position[0],
							anim->base_object->position[1],
							anim->base_object->position[2]);
	ml_vector3_copy((t_vec3){anim->base_object->position[0],
				anim->base_object->position[1],
				anim->base_object->position[2]},
				anim->frame_object_prev_translation[
					anim->frames_start_idx + anim->current_frame]);
}

/*
**	Updates the npc position to current animation frame
*/

void		npc_anim_3d_rotation_update(t_animation_3d *anim)
{
	t_mat4				inverse_rot;

	if (anim == NULL || anim->current_object == NULL ||
		anim->base_object == NULL)
	{
		return ;
	}
	ml_matrix4_inverse(anim->current_object->rotation , inverse_rot);
	l3d_3d_object_rotate_matrix(anim->current_object, inverse_rot);
	l3d_3d_object_rotate_matrix(anim->current_object,
								anim->base_object->rotation);
}

static t_bool			frame_time_expired(t_doom3d *app,
											t_animation_3d *animation)
{
	return (((app->current_tick - animation->tick_at_update) %
		(TICKS_PER_SEC)) > (TICKS_PER_SEC / ANIM_3D_FPS));
}

static t_bool			anim_3d_clip_ended(t_animation_3d *animation)
{
	return (animation->current_frame > animation->clip_info[animation->
			current_clip % ANIM_3D_TYPE_MOD].clip_length +
				animation->anim_clip_start_indices[
					animation->current_clip % ANIM_3D_TYPE_MOD] - 1);
}

static t_bool			instance_status_check(t_animation_3d *animation,
												float elapsed_time,
												uint32_t clip_length)
{
	static t_bool	event_f_triggered = false;

	if (elapsed_time >= animation->current_anim_instance->trigger_time &&
		!event_f_triggered)
	{
		animation->current_anim_instance->
			f_event(animation->current_anim_instance->app,
					animation->current_anim_instance->params);
		event_f_triggered = true;
	}
	if (animation->base_object == NULL || animation == NULL)
	{
		return (false);
	}
	if (elapsed_time >= (float)(clip_length - 1) / (float)clip_length)
		{
			animation->current_anim_instance->active = false;
			return (false);
		}
	else
	{
		return (true);
	}
}

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
	animation->current_object =
		animation->animation_frames[animation->current_frame];
	elapsed_time = (float)(animation->current_frame - clip_start_idx) /
					(float)clip_length;
	instance_status_check(animation, elapsed_time, clip_length);
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

void test_print(void *params)
{
	ft_printf("test print anim event current frame %d \n",
		((t_npc*)params)->animation_3d->current_frame);
}

uint32_t				anim_3d_loop_update(t_doom3d *app, t_animation_3d *animation)
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

static void				test_event(t_doom3d *app, void** params)
{
	push_custom_event(app, event_object_delete, params[0], params[1]);
}

uint32_t				anim_3d_frame_update(t_doom3d *app, t_animation_3d *animation)
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
	static int c = 0;
	c++;
	t_anim_3d_instance inst;
	inst.active = true;
	inst.anim_clip = anim_3d_type_death;
	inst.f_event = test_event;
	// inst.f_event = test_print;
	inst.params[0] = (t_3d_object*)(animation->base_object);
	inst.params[1] = NULL;
	inst.params[2] = NULL;
	inst.start_frame = 0;
	inst.trigger_time = 0.9;

	if (c == 300)
		anim_3d_clip_play(app, animation->base_object, &inst);

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
		LOG_ERROR("Tried to set animation clip to an object with no animation_3d");
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


/*
**	Plays the given animation clip
*/
// typedef struct				s_anim_3d_instance
// {
// 	void					(*f_event)(void*);
// 	t_animation_3d_type		anim_clip;
// 	float					trigger_time;
// 	int32_t					start_frame;
// 	t_bool					active;
// }							t_anim_3d_instance;

void					copy_instance_data(t_animation_3d *anim,
											t_anim_3d_instance *instance)
{
	anim->current_anim_instance->active = instance->active;
	anim->current_anim_instance->anim_clip = instance->anim_clip;
	anim->current_anim_instance->f_event = instance->f_event;
	anim->current_anim_instance->start_frame = instance->start_frame;
	anim->current_anim_instance->trigger_time = instance->trigger_time;
	anim->current_anim_instance->params[0] = instance->params[0];
	anim->current_anim_instance->params[1] = instance->params[1];
	anim->current_anim_instance->params[2] = instance->params[2];

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


t_bool					check_obj_3d_anim(t_3d_object *obj)
{
	if (!(obj->type == object_type_npc && ((t_npc*)obj->params)->animation_3d != NULL))
	{
		LOG_ERROR("Tried to access 3D animation of an object with no animation_3d");
		return false;
	}
	else
		return (true);
}