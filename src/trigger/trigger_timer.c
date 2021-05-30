/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:24:06 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/30 19:09:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	trigger_timer_start(t_doom3d *app, t_3d_object *obj, int type)
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
			app->timer[i].type = type;
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
				if (app->timer[i].type == timer_switch)
					elevator_go_to_next_node(app, app->timer[i].target);
				if (app->timer[i].type == timer_end)
				{
					push_custom_event(app, event_scene_change,
						(void *)scene_id_main_menu, NULL);
					notify_user(app, (t_notification){.message = "The End",
						.time = 6000, .type = notification_type_layer});
				}
				app->timer[i].active = false;
				if (app->settings.is_debug)
					LOG_DEBUG("Finished timer in slot %d", i);
			}
		}
	}
}
