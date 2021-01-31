/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_3d.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:52:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/29 19:58:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONS_3D_H
# define ANIMATIONS_3D_H

# define TICKS_PER_SEC 48
# define ANIM_3D_FPS 12
# define ANIM_3D_FRAME_MAX 256
# define ANIM_3D_CLIP_LENGTH_MAX 32
# define ANIM_3D_COUNT_MAX 64
# define ANIM_3D_TYPE_MOD 1000

# include "libft.h"
# include "lib3d.h"

/*
**	The enum values are encoded with ANIM_3D_TYPE_MOD and can be decoded using
**	% to get the array indices for referencing
*/

typedef enum				e_animation_3d_type
{
	anim_3d_type_idle = 0 + ANIM_3D_TYPE_MOD,
	anim_3d_type_move = 1 + ANIM_3D_TYPE_MOD,
	anim_3d_type_attack = 2 + ANIM_3D_TYPE_MOD,
	anim_3d_type_death = 3 + ANIM_3D_TYPE_MOD
}							t_animation_3d_type;

typedef struct				s_anim_metadata
{
	uint32_t				frame_count;
	uint32_t				frames_start_idx;
	uint32_t				anim_count;
	uint32_t				clip_lengths[ANIM_3D_COUNT_MAX];
	uint32_t				anim_frame_numbers[ANIM_3D_FRAME_MAX];
}							t_anim_metadata;

/*
**	Contains the info for each animation clip. anim_frame_numbers contains
**	the indices for each frame in the clip in the animation_frames array;
*/

typedef struct				s_anim_3d_clip_info
{
	uint32_t				anim_frame_numbers[ANIM_3D_CLIP_LENGTH_MAX];
	uint32_t				clip_length;
}							t_anim_3d_clip_info;

typedef struct				s_animation_3d
{
	uint32_t				frame_count;
	uint32_t				frames_start_idx;
	uint32_t				anim_count;
	uint32_t				current_frame;
	t_animation_3d_type		current_clip;
	uint32_t				start_frame;
	uint32_t				start_tick;
	t_3d_object				*base_object;
	t_3d_object				*animation_frames[ANIM_3D_FRAME_MAX]; //contains the objects for each anim frame
	t_anim_3d_clip_info		clip_info[ANIM_3D_COUNT_MAX];	
}							t_animation_3d;

#endif