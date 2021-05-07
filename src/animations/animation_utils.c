/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:02:34 by veilo             #+#    #+#             */
/*   Updated: 2021/05/07 14:28:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	update_app_ticks(t_doom3d *app)
{
	app->current_tick = (SDL_GetPerformanceCounter() * TICKS_PER_SEC)
		/ SDL_GetPerformanceFrequency();
}

void	copy_instance_data(t_animation_3d *anim,
											t_anim_3d_instance *instance)
{
	anim->current_anim_instance->active = instance->active;
	anim->current_anim_instance->anim_clip = instance->anim_clip;
	anim->current_anim_instance->f_event = instance->f_event;
	anim->current_anim_instance->start_frame = instance->start_frame;
	anim->current_anim_instance->trigger_time = instance->trigger_time;
	anim->current_anim_instance->event_triggered = instance->event_triggered;
	anim->current_anim_instance->params[0] = instance->params[0];
	anim->current_anim_instance->params[1] = instance->params[1];
	anim->current_anim_instance->params[2] = instance->params[2];
}

t_bool	check_obj_3d_anim(t_3d_object *obj)
{
	if (!(obj->type == object_type_npc
			&& ((t_npc*)obj->params)->animation_3d != NULL))
	{
		LOG_ERROR("Tried to access 3D animation of an"
			" object with no animation_3d");
		return (false);
	}
	else
		return (true);
}
