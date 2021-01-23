/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_animation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:51 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/23 17:15:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_ANIMATION_H
# define MODEL_ANIMATION_H

# include "libft.h"
# include "lib3d.h"

# define TICKS_PER_SEC 48
# define ANIM_3D_FPS 12
# define ANIM_3D_MAX_COUNT 16
# define ANIM_FRAME_TIME_MS 100

typedef enum				e_animation_type
{
	anim_idle,
	anim_move,
	anim_attack,
	anim_death
}							t_animation_type;

typedef struct				s_anim_metadata
{
	uint32_t				frame_count;
	uint32_t				anim_count;
	uint32_t				scene_frame_key_indices[ANIM_3D_MAX_COUNT];
	uint32_t				anim_frame_numbers[ANIM_3D_MAX_COUNT];
}							t_anim_metadata;

typedef struct				s_animation
{
	uint32_t				frame_count;
	uint32_t				anim_count;
	uint32_t				current_frame;
	uint32_t				start_frame;
	uint32_t				start_tick;
	t_3d_object				*base_object;
	t_3d_object				**animation_frames; //contains the objects for each anim frame
	int32_t					anim_frame_numbers[ANIM_3D_MAX_COUNT]; //contains the frame indices for each animation start
}							t_animation;

#endif