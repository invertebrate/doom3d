/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_sound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phakakos <phakakos@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:12:25 by phakakos          #+#    #+#             */
/*   Updated: 2021/05/12 22:12:29 by phakakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_jukebox(t_doom3d *app, t_3d_object *obj)
{
	int32_t	log_id;

	if (((t_trigger *)(obj->params))->key_id < 0
		|| ((t_trigger *)(obj->params))->key_id > 19)
		return ;
	obj->params_type = trigger_type_disabled;
	log_id = sf_audio_log_1 + ((t_trigger *)(obj->params))->key_id;
	push_custom_event(app, event_effect_play, (void *)(intptr_t)log_id,
		s_ini(0, 1, st_game, 1));
	show_subtitle(app, log_id);
	push_custom_event(app, event_object_delete, obj, NULL);
}

void	handle_musicbox(t_doom3d *app, t_3d_object *obj)
{
	int32_t	log_id;

	if (((t_trigger *)(obj->params))->key_id < 0)
		return ;
	else if (((t_trigger *)(obj->params))->key_id >= MUSIC)
		log_id = ((t_trigger *)(obj->params))->key_id % MUSIC;
	else
		log_id = mu_main + ((t_trigger *)(obj->params))->key_id;
	LOG_INFO("Music change");
	mp_typec(app, 0, 1, SSTOPPED);
	push_custom_event(app, event_music_play,
		(void *)(intptr_t)log_id, s_ini(1, 10, st_game, 1.0f));
	obj->params_type = trigger_type_disabled;
	push_custom_event(app, event_object_delete, obj, NULL);
}

void	trigger_handle_trigger_jukebox(t_doom3d *app, t_3d_object *key,
												t_trigger *trigger)
{
	int32_t	key_id;

	trigger = key->params;
	key_id = app->editor.patrol_slot;
	if (key->params_type == trigger_jukebox
		&& app->editor.patrol_slot < AUDIO_LOG)
	{
		trigger->key_id = app->editor.patrol_slot;
		LOG_INFO("Key id set to slot %d", key_id);
	}
	else if (key->params_type == trigger_musicbox)
	{
		if (key_id >= MUSIC)
			key_id = key_id % MUSIC;
		trigger->key_id = key_id;
		LOG_INFO("Key id set to slot %d", key_id);
	}
	LOG_INFO("Edited box track");
}
