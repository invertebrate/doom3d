/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:57:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 18:40:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	match_editor_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_editor_start_placement)
		ft_sprintf(str, "EditorStartPlacement");
	else if (code == event_editor_start_placement)
		ft_sprintf(str, "EditorEndPlacement");
	else if (code == event_editor_start_save)
		ft_sprintf(str, "EditorStartSave");
	else if (code == event_editor_end_save)
		ft_sprintf(str, "EditorEndSave");
	else if (code == event_editor_save_type)
		ft_sprintf(str, "EditorType");
	else if (code == event_editor_save_type_backspace)
		ft_sprintf(str, "EditorTypeBackspace");
	else if (code == event_editor_delete)
		ft_sprintf(str, "EditorDelete");
	else if (code == event_editor_select)
		ft_sprintf(str, "EditorSelect");
	else if (code == event_editor_deselect)
		ft_sprintf(str, "EditorDeselect");
	else if (code == event_editor_level_switch)
		ft_sprintf(str, "EditorLevelSwitch");
	else if (code == event_editor_exit)
		ft_sprintf(str, "EditorExit");
}

static void	doom3d_custom_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_object_delete)
		ft_sprintf(str, "ObjectDelete");
	else if (code == event_music_play)
		ft_sprintf(str, "MusicPlay");
	else if (code == event_effect_play)
		ft_sprintf(str, "EffectPlay");
	else if (code == event_scene_change)
		ft_sprintf(str, "SceneChange");
	else if (code == event_scene_reload)
		ft_sprintf(str, "SceneReload");
	else if (code == event_quit)
		ft_sprintf(str, "Quit");
	else if (code == event_window_resize)
		ft_sprintf(str, "WindowResize");
	match_editor_event_to_str(str, code);
}

void		register_editor_events(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_editor_start_placement,
		(void*)handle_editor_placement_start);
	hash_map_add(app->custom_event_handles, event_editor_end_placement,
		(void*)handle_editor_placement_end);
	hash_map_add(app->custom_event_handles, event_editor_start_save,
		(void*)handle_editor_save_start);
	hash_map_add(app->custom_event_handles, event_editor_end_save,
		(void*)handle_editor_save_end);
	hash_map_add(app->custom_event_handles, event_editor_save_type,
		(void*)handle_editor_save_type);
	hash_map_add(app->custom_event_handles, event_editor_save_type_backspace,
		(void*)handle_editor_save_type_backspace);
	hash_map_add(app->custom_event_handles, event_editor_delete,
		(void*)handle_editor_delete);
	hash_map_add(app->custom_event_handles, event_editor_exit,
		(void*)handle_editor_exit);
	hash_map_add(app->custom_event_handles, event_editor_select,
		(void*)handle_editor_select);
	hash_map_add(app->custom_event_handles, event_editor_deselect,
		(void*)handle_editor_deselect);
	hash_map_add(app->custom_event_handles, event_editor_level_switch,
		(void*)handle_editor_level_switch);
}

/*
** Registers all custom events and their handlers
** Caller must know what to input to handlers in event handling
*/

void		doom3d_register_custom_events(t_doom3d *app)
{
	app->custom_event_type = SDL_RegisterEvents(1);
	app->custom_event_handles = hash_map_create(NUM_CUSTOM_EVENTS);
	hash_map_add(app->custom_event_handles, event_object_delete,
		(void*)handle_object_deletion);
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
	hash_map_add(app->custom_event_handles, event_quit,
		(void*)handle_quit);
	register_editor_events(app);
}

void		doom3d_push_event(t_doom3d *app,
								t_doom3d_event code,
								void* data1,
								void* data2)
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

void		doom3d_events_handle(t_doom3d *app, SDL_Event event)
{
	void		(*handle)(void*, void*, void*);
	char		event_str[64];

	handle = hash_map_get(app->custom_event_handles, event.user.code);
	if (handle != NULL)
	{
		doom3d_custom_event_to_str(event_str, event.user.code);
		ft_printf("Event: %s\n", event_str);
		handle(app, event.user.data1, event.user.data2);
	}
}