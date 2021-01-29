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

# include "libft.h"
# include "lib3d.h"

typedef struct				s_anim_metadata
{
	uint32_t				frame_count;
	uint32_t				frames_start_idx;
	uint32_t				anim_count;
	uint32_t				anim_frame_numbers[ANIM_3D_FRAME_MAX];
}							t_anim_metadata;

typedef struct				s_animation_3d
{
	uint32_t				frame_count;
	uint32_t				frames_start_idx;
	uint32_t				anim_count;
	uint32_t				current_frame;
	uint32_t				start_frame;
	uint32_t				start_tick;
	t_3d_object				*base_object;
	t_3d_object				*animation_frames[ANIM_3D_FRAME_MAX]; //contains the objects for each anim frame
	int32_t					anim_frame_numbers[ANIM_3D_FRAME_MAX]; //contains the frame indices for each animation start
}							t_animation_3d;

#endif