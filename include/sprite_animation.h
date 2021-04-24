/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:07:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:33:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_ANIMATION_H
# define SPRITE_ANIMATION_H

# include "libft.h"

# define MAX_ANIMATION_FRAMES 16

typedef struct				s_anim_frame
{
	int32_t		x_offset;
	int32_t		y_offset;
	int32_t		width;
	int32_t		height;
}							t_anim_frame;

/*
** @id: Animation id, e.g. t_player_animation anim_shotgun_shoot
** @frames: frame information, dimensions and offsets
** @current_frame: index of currently shown frame
** @frame_time: how long each frame is shown
** @frame_time_left: update decrements this until <= 0 and moves on to next
** @interruptable: whether animation can be interrupted
** @is_finised: when last frame is shown, animation is set to be finished
** uninterruptable animations are not overridden unless they are finised
*/

typedef struct				s_sprite_anim
{
	t_anim_frame			frames[MAX_ANIMATION_FRAMES];
	int32_t					num_frames;
	int32_t					current_frame;
	int32_t					frame_time;
	int32_t					frame_time_left;
	t_bool					interruptable;
	t_bool					is_finished;
}							t_sprite_anim;

#endif