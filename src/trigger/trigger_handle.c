/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:55:31 by veilo             #+#    #+#             */
/*   Updated: 2021/05/31 15:18:25 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	trigger_handle_door_switch(t_doom3d *app, t_trigger *trigger)
{
	if (trigger->linked_obj[0])
	{
		elevator_go_to_next_node(app, trigger->linked_obj[0]);
		push_custom_event(app, event_effect_play,
			(void *)sf_door_open, s_ini(0, 1, st_game, 1.0));
	}
	trigger_timer_start(app, trigger->linked_obj[0], timer_switch, 10000);
}

void	trigger_handle_elevator_switch(t_doom3d *app,
												t_trigger *trigger)
{
	if (trigger->linked_obj[0])
	{
		if (trigger->key_id == -1
			|| app->player.keys[trigger->key_id] == true)
		{
			elevator_go_to_next_node(app, trigger->linked_obj[0]);
			push_custom_event(app, event_effect_play,
				(void *)sf_door_open, s_ini(0, 1, st_game, 1.0));
		}
		else
		{
			LOG_INFO("Player is missing key!");
			push_custom_event(app, event_effect_play,
				(void *)sf_door_locked, s_ini(0, 1, st_game, 1.0));
		}
	}
	else
	{
		LOG_INFO("Keypad not linked to anything!");
		push_custom_event(app, event_effect_play,
			(void *)sf_door_locked, s_ini(0, 1, st_game, 1.0));
	}
}
