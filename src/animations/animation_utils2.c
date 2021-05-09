/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:01:32 by veilo             #+#    #+#             */
/*   Updated: 2021/05/07 14:22:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_bool	frame_time_expired(t_doom3d *app,
											t_animation_3d *animation)
{
	return (((app->current_tick - animation->tick_at_update)
			% (TICKS_PER_SEC)) > (TICKS_PER_SEC / ANIM_3D_FPS));
}

t_bool	anim_3d_clip_ended(t_animation_3d *animation)
{
	return (animation->current_frame > animation->clip_info[animation
			->current_clip % ANIM_3D_TYPE_MOD].clip_length
		+ animation->anim_clip_start_indices[
			animation->current_clip % ANIM_3D_TYPE_MOD] - 1);
}

/*
**	Checks the animation instance if the trigger time has passed
*/

t_bool	instance_status_check(t_animation_3d *animation,
												float elapsed_time)
{
	if (elapsed_time >= animation->current_anim_instance->trigger_time
		&& !animation->current_anim_instance->event_triggered)
	{
		animation->current_anim_instance->
			f_event(animation->current_anim_instance->app,
					animation->current_anim_instance->params);
		animation->current_anim_instance->event_triggered = true;
	}
	if (animation->base_object == NULL || animation == NULL)
	{
		return (false);
	}
	if (elapsed_time >= 1.0)
	{
		animation->current_anim_instance->active = false;
		animation->current_anim_instance->event_triggered = false;
		return (false);
	}
	else
	{
		return (true);
	}
}
