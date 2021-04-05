/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:57:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 14:05:10 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	custom_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_music_play)
		ft_sprintf(str, "event_music_play");
	else if (code == event_effect_play)
		ft_sprintf(str, "event_effect_play");
	else if (code == event_scene_change)
		ft_sprintf(str, "event_scene_change");
	else if (code == event_scene_reload)
		ft_sprintf(str, "event_scene_reload");
	else if (code == event_quit)
		ft_sprintf(str, "event_quit");
	else if (code == event_toggle_fullscreen)
		ft_sprintf(str, "event_toggle_fullscreen");
	else if (code == event_toggle_debug_mode)
		ft_sprintf(str, "event_toggle_debug_mode");
	else if (code == event_toggle_pause_game)
		ft_sprintf(str, "event_toggle_pause_game");
	else if (code == event_toggle_normal_map_mode)
		ft_sprintf(str, "event_toggle_normal_map_mode");
	else if (code == event_window_resize)
		ft_sprintf(str, "event_window_resize");
	editor_custom_event_to_str(str, code);
	object_custom_event_to_str(str, code);
	player_custom_event_to_str(str, code);
}

void		register_control_flow_custom_events(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_quit,
		(void*)handle_quit);
	hash_map_add(app->custom_event_handles, event_toggle_fullscreen,
		(void*)handle_toggle_fullscreen);
	hash_map_add(app->custom_event_handles, event_toggle_debug_mode,
		(void*)handle_toggle_debug_mode);
	hash_map_add(app->custom_event_handles, event_toggle_pause_game,
		(void*)handle_toggle_pause_game);
	hash_map_add(app->custom_event_handles, event_toggle_normal_map_mode,
		(void*)handle_toggle_normal_map_mode);
}

/*
** Registers all custom events and their handlers
** Caller must know what to input to handlers in event handling
*/

void		register_custom_events(t_doom3d *app)
{
	app->custom_event_type = SDL_RegisterEvents(1);
	app->custom_event_handles = hash_map_create(NUM_CUSTOM_EVENTS);
	hash_map_add(app->custom_event_handles, event_effect_play,
		(void*)handle_play_effect);
	hash_map_add(app->custom_event_handles, event_music_play,
		(void*)handle_play_music);
	hash_map_add(app->custom_event_handles, event_window_resize,
		(void*)handle_window_resize);
	hash_map_add(app->custom_event_handles, event_scene_change,
		(void*)handle_scene_change);
	hash_map_add(app->custom_event_handles, event_scene_reload,
		(void*)handle_scene_reload);
	register_control_flow_custom_events(app);
	register_editor_custom_events(app);
	register_object_custom_events(app);
	register_player_custom_events(app);
}

void		push_custom_event(t_doom3d *app,
								t_doom3d_event code,
								void *data1,
								void *data2)
{
	SDL_Event event;

	ft_memset(&event, 0, sizeof(event));
	event.type = app->custom_event_type;
	event.user.code = code;
	event.user.data1 = data1;
	event.user.data2 = data2;
	SDL_PushEvent(&event);
}

/*
** Note that this is rather unsafe code here:
** 1. Push event will set data1 and data2. These should be sufficient to contain
** any event data.
** 2. Handler should not have more than 3 inputs. App, data1, data2.
** 3. All handlers must have been registered at the beginning of the app
*/

void		handle_custom_events(t_doom3d *app, SDL_Event event)
{
	void		(*handle)(void*, void*, void*);
	char		event_str[128];

	handle = hash_map_get(app->custom_event_handles, event.user.code);
	if (handle != NULL)
	{
		custom_event_to_str(event_str, event.user.code);
		ft_printf("Event:%d: %s(app, %p, %p)\n",
			event.user.code, event_str, event.user.data1, event.user.data2);
		handle(app, event.user.data1, event.user.data2);
	}
}
