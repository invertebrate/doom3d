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

/*
**	Updates the npc position to current animation frame
*/

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
	l3d_3d_object_translate(anim->current_object, obj->position[0],
							obj->position[1], obj->position[2]);
	ml_vector3_copy((t_vec3){obj->position[0], obj->position[1], obj->position[2]},
						anim->frame_object_prev_translation[anim->frames_start_idx + anim->current_frame]);
}

/*
**	Updates the npc position to current animation frame
*/

void		npc_anim_3d_rotation_update(t_3d_object *obj)
{
	t_animation_3d		*anim;
	t_mat4				inverse_rot;

	anim = NULL;
	if (obj->type == object_type_npc && ((t_npc*)obj->params)->animation_3d != NULL)
		anim = ((t_npc*)obj->params)->animation_3d;
	else
		return ;
	ml_matrix4_inverse(anim->current_object->rotation , inverse_rot);
	l3d_3d_object_rotate_matrix(anim->current_object, inverse_rot);
	l3d_3d_object_rotate_matrix(anim->current_object, obj->rotation);
}

uint32_t				handle_anim_instance(t_doom3d *app, t_animation_3d *animation)
{
	uint32_t	current_frame;
	float		elapsed_time;

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
	elapsed_time = (animation->current_frame - animation->anim_clip_start_indices[animation->current_clip % ANIM_3D_TYPE_MOD]) /
					animation->clip_info[animation->current_clip % ANIM_3D_TYPE_MOD].clip_length;
	if (elapsed_time >= animation->current_anim_instance->trigger_time)
		animation->current_anim_instance->f_event(animation->current_anim_instance->params);
	npc_anim_3d_position_update(animation->base_object);
	npc_anim_3d_rotation_update(animation->base_object);
	return (current_frame);
}

void test_print(void *params)
{
	ft_printf("test print anim event current frame %d \n", ((t_npc*)params)->animation_3d->current_frame);
}

uint32_t				anim_3d_frame_update(t_doom3d *app, t_animation_3d *animation)
{
	uint32_t	current_frame;

	if (animation->current_clip == anim_3d_type_null)
	{
		npc_anim_3d_position_update(animation->base_object);
		npc_anim_3d_rotation_update(animation->base_object);
		return (UINT32_MAX);
	}
	// if (animation->current_anim_instance->active == true)
	// {
	// 	return (handle_anim_instance(app, animation));
	// }
	static int c = 0;
	c++;
	// t_anim_3d_instance inst;
	// inst.active = true;
	// inst.anim_clip = anim_3d_type_death;
	// // inst.f_event = (void*)npc_destroy;
	// inst.f_event = test_print;
	// inst.params = (t_npc*)animation->base_object->params;
	// inst.start_frame = 0;
	// inst.trigger_time = 1.0;


	// (void)inst;
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
	npc_anim_3d_rotation_update(animation->base_object);
	if (c == 500)
	{
	// 	// void					anim_3d_clip_set(t_doom3d *app, t_3d_object *obj,
	// 	// 								t_animation_3d_type clip, uint32_t start_frame)
		ft_printf("clip set\n");
		anim_3d_clip_set(app, animation->base_object, anim_3d_type_death, 0);
		// anim_3d_clip_play(app, animation->base_object, &inst);
	}
	return (current_frame);
}

/*
**	Changes the current playing animation clip of an object
*/

void					anim_3d_clip_set(t_doom3d *app, t_3d_object *obj,
										t_animation_3d_type clip, uint32_t start_frame)
{
	t_animation_3d		*anim;

	if (!(check_obj_3d_anim(obj)))
	{
		LOG_ERROR("Tried to set animation clip to an object with no animation_3d");
		return ;
	}
	anim = ((t_npc*)obj->params)->animation_3d;
	anim->current_clip = clip;
	anim->current_frame = start_frame;
	anim->current_object = anim->animation_frames[anim->anim_clip_start_indices[clip %
													ANIM_3D_TYPE_MOD] + start_frame];
	ft_printf("clip: %d start indices: %d\n", clip,  anim->anim_clip_start_indices[clip %
													ANIM_3D_TYPE_MOD]);
	anim->tick_at_update = app->current_tick;
	npc_anim_3d_position_update(obj);
	npc_anim_3d_rotation_update(obj);
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

void					copy_instance_data(t_animation_3d *anim, t_anim_3d_instance *instance)
{
	anim->current_anim_instance->active = instance->active;
	anim->current_anim_instance->anim_clip = instance->anim_clip;
	anim->current_anim_instance->f_event = instance->f_event;
	anim->current_anim_instance->start_frame = instance->start_frame;
	anim->current_anim_instance->trigger_time = instance->trigger_time;
}

t_bool					anim_3d_clip_play(t_doom3d *app, t_3d_object *obj,
										t_anim_3d_instance *anim_instance)
{
	t_animation_3d		*anim;

	if (!(check_obj_3d_anim(obj)))
	{
		LOG_ERROR("Tried to play animation clip of an object with no animation_3d");
		return false;
	}
	else if (anim_instance == NULL || anim_instance->f_event == NULL)
	{
		LOG_ERROR("Tried to play animation clip with invalid instance data");
		return false;
	}
	ft_printf("PLAY!\n");
	anim = ((t_npc*)obj->params)->animation_3d;
	copy_instance_data(anim, anim_instance);
	anim->current_clip = anim->current_anim_instance->anim_clip;
	anim->current_frame = anim->current_anim_instance->start_frame;
	anim->current_anim_instance->active = true;
	anim->current_object = anim->animation_frames[anim->anim_clip_start_indices[anim_instance->anim_clip %
													ANIM_3D_TYPE_MOD]];
	anim->tick_at_update = app->current_tick;
	npc_anim_3d_position_update(obj);
	npc_anim_3d_rotation_update(obj);
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