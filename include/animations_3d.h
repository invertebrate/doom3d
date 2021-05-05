/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_3d.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:52:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:01:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONS_3D_H
# define ANIMATIONS_3D_H

# define TICKS_PER_SEC 48
# define ANIM_3D_FPS 12
# define ANIM_3D_FRAME_MAX 512
# define ANIM_3D_CLIP_LENGTH_MAX 512
# define ANIM_3D_COUNT_MAX 512
# define ANIM_3D_TYPE_MOD 1000

# include "doom3d.h"
# include "libft.h"
# include "lib3d.h"

/*
**	The enum values are encoded with ANIM_3D_TYPE_MOD and can be decoded using
**	% to get the array indices for referencing.
**	0 is basically static base_object.
*/

typedef enum e_animation_3d_type
{
	anim_3d_type_null = 0 + ANIM_3D_TYPE_MOD,
	anim_3d_type_idle = 1 + ANIM_3D_TYPE_MOD,
	anim_3d_type_move = 2 + ANIM_3D_TYPE_MOD,
	anim_3d_type_attack = 3 + ANIM_3D_TYPE_MOD,
	anim_3d_type_death = 4 + ANIM_3D_TYPE_MOD
}							t_animation_3d_type;

typedef struct s_anim_metadata
{
	uint32_t				frame_count;
	uint32_t				frames_start_idx;
	uint32_t				anim_count;
	uint32_t				clip_lengths[ANIM_3D_COUNT_MAX];
	uint32_t				anim_frame_numbers[ANIM_3D_FRAME_MAX];
	uint32_t				anim_clip_start_indices[ANIM_3D_COUNT_MAX];
}							t_anim_metadata;

/*
**	Contains the info for each animation clip. anim_frame_numbers contains
**	the indices for each frame in the clip in the animation_frames array;
*/
typedef struct s_anim_3d_clip_info
{
	uint32_t				anim_frame_numbers[ANIM_3D_CLIP_LENGTH_MAX];
	uint32_t				clip_length;
}							t_anim_3d_clip_info;

/*
**	Is used to pass data to play_3d_animation function to run a single play
**	animation clip with an event function and trigger time. Trigger time is
**	between 0-1 as a proportion of the entire clip length e.g. 0.25 meaning it
**	will trigger when 25% of the clip has been played, accurate within 1/12
**	of a second. If the start frame is lower in time than the trigger time,
**	the behaviour is undefined.
*/

typedef struct s_anim_3d_instance
{
	struct s_doom3d			*app;
	void					(*f_event)(struct s_doom3d*, void**);
	void					*params[3];
	t_animation_3d_type		anim_clip;
	float					trigger_time;
	t_bool					event_triggered;
	int32_t					start_frame;
	t_bool					active;
}							t_anim_3d_instance;

/*
**	Contains all the data required for running 3D animations for an object.
** 3d animation struct containing required data to switch between rendered
** 3d objects under the animated object owning this data.
*/

typedef struct s_animation_3d
{
	uint32_t				frame_count;
	uint32_t				frames_start_idx;
	uint32_t				anim_clip_start_indices[ANIM_3D_COUNT_MAX];
	uint32_t				anim_count;
	uint32_t				current_frame;
	t_animation_3d_type		current_clip;
	uint32_t				start_frame;
	uint32_t				tick_at_update;
	t_3d_object				*base_object;
	t_3d_object				*current_object;
	t_3d_object				*animation_frames[ANIM_3D_FRAME_MAX];
	t_vec3					frame_object_prev_translation[ANIM_3D_FRAME_MAX];
	t_mat4					frame_object_prev_rotation[ANIM_3D_FRAME_MAX];
	t_anim_3d_clip_info		clip_info[ANIM_3D_COUNT_MAX];
	t_anim_3d_instance		*current_anim_instance;
}							t_animation_3d;

#endif
