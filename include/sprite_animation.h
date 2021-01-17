/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:07:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/15 15:08:10 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_ANIMATION_H
# define SPRITE_ANIMATION_H

#include "libft.h"

typedef struct				s_anim_frame
{
	int32_t		x_offset;
	int32_t		y_offset;
	int32_t		width;
	int32_t		height;
}							t_anim_frame;

typedef struct				s_sprite_anim
{
	uint32_t				id;
	t_anim_frame			frames[16];
	int32_t					num_frames;
	int32_t					current_frame;
	int32_t					frame_time;
	int32_t					frame_time_left;
	t_bool					interruptable;
	t_bool					is_finished;
}							t_sprite_anim;

#endif