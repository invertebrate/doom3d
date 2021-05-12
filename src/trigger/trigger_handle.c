/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:55:31 by veilo             #+#    #+#             */
/*   Updated: 2021/05/12 10:11:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	show_subtitle(t_doom3d *app, int32_t log_id)
{
	const char	*subtitle;

	subtitle = get_subtitle_by_log_id(log_id);
	notify_user(app, (t_notification){
		.message = subtitle, .type = notification_type_story});
}

void	handle_jukebox(t_doom3d *app, t_3d_object *obj)
{
	int32_t	log_id;

	if (((t_trigger *)(obj->params))->key_id < 0
		|| ((t_trigger *)(obj->params))->key_id > 19)
		return ;
	if (((t_trigger *)(obj->params))->key_id == 17)
	{
		LOG_INFO("SHOULD CHANGE MUSIC!");
		mp_typec(app, 0, 0, SSTOPPED);
		push_custom_event(app, event_music_play,
			(void *)mu_doom, s_ini(1, 10, st_main_menu, 0.3));
	}
	obj->params_type = trigger_type_disabled;
	log_id = sf_audio_log_1 + ((t_trigger *)(obj->params))->key_id;
	push_custom_event(app, event_effect_play, (void *)(intptr_t)log_id,
		s_ini(0, 1, st_game, 1));
	show_subtitle(app, log_id);
	push_custom_event(app, event_object_delete, obj, NULL);
}

void	trigger_handle_trigger_jukebox(t_doom3d *app, t_3d_object *key,
												t_trigger *trigger)
{
	trigger = key->params;
	if (app->editor.patrol_slot < AUDIO_LOG)
	{
		trigger->key_id = app->editor.patrol_slot;
		LOG_INFO("Key id set to slot %d", app->editor.patrol_slot);
	}
	LOG_INFO("Edited jukebox track");
}

void	trigger_handle_door_switch(t_doom3d *app, t_trigger *trigger)
{
	if (trigger->linked_obj[0])
	{
		elevator_go_to_next_node(app, trigger->linked_obj[0]);
		push_custom_event(app, event_effect_play,
			(void *)sf_door_open, s_ini(0, 1, st_game, 1.0));
	}
	trigger_timer_start(app, trigger->linked_obj[0], timer_switch);
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
}
