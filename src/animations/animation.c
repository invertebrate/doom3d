/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2020/12/30 20:32:36 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			update_app_ticks(t_doom3d *app)
{
	app->current_tick = (SDL_GetPerformanceCounter() * TICKS_PER_SEC) /
						SDL_GetPerformanceFrequency();
}

uint32_t		update_current_frame(t_doom3d *app, t_3d_object *object)
{
	uint32_t	current_frame;

	current_frame = ((t_animation*)object->params)->start_frame +
	((app->current_tick - ((t_animation*)object->params)->start_tick) % (int)(TICKS_PER_SEC / ANIM_3D_FPS));
	((t_animation*)object->params)->current_frame = current_frame;
	return (current_frame);
}
//TODO LOG
//figure out how to get framecount to animation struct
//figure out how to get the anim frames key ** pointer out of the function 