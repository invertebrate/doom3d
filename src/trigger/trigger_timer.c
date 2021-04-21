/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:24:06 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/21 16:49:26 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	trigger_timer_start(t_doom3d *app, t_3d_object *obj)
{
	int		i;
	int		timer_length;

	i = -1;
	timer_length = 10000;
	while (++i < MAX_TIMERS)
	{
		if (!app->timer[i].active)
		{
			app->timer[i].active = true;
			app->timer[i].target = obj;
			app->timer[i].timer_end = (int)SDL_GetTicks() + timer_length;
			LOG_INFO("Started timer in slot %d", i);
		}
	}
}

void	trigger_timer_update(t_doom3d *app)
{
	int		i;
	int		current_time;

	i = -1;
	current_time = (int)SDL_GetTicks();
	while (++i < MAX_TIMERS)
	{
		if (app->timer[i].active)
		{
			if (app->timer[i].timer_end - current_time < 0)
			{
				elevator_go_to_next_node(app, app->timer[i].target);
				app->timer[i].active = false;
				LOG_INFO("Finished timer in slot %d", i);
			}
		}
	}
}