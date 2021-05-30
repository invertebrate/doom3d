/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 15:24:06 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/30 20:13:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	trigger_timer_start(t_doom3d *app, t_3d_object *obj,
			int32_t type, int32_t timer_length)
{
	int		i;

	i = -1;
	while (++i < MAX_TIMERS)
	{
		if (!app->timer[i].active)
		{
			app->timer[i].active = true;
			app->timer[i].target = obj;
			app->timer[i].type = type;
			app->timer[i].timer_end = (int)SDL_GetTicks() + timer_length;
			break ;
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
		if (app->timer[i].active
			&& app->timer[i].timer_end - current_time < 0)
		{
			if (app->timer[i].type == timer_switch
				&& app->timer[i].target != NULL)
				elevator_go_to_next_node(app, app->timer[i].target);
			if (app->timer[i].type == timer_end)
			{
				push_custom_event(app, event_scene_change,
					(void *)scene_id_main_menu, NULL);
				notify_user(app, (t_notification){.message = "The End",
					.time = 10000, .type = notification_type_layer});
			}
			ft_memset(&app->timer[i], 0, sizeof(app->timer[i]));
		}
	}
}
