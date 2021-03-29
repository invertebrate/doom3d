/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom3d_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:57:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 16:16:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	doom3d_custom_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_delete_object)
		ft_sprintf(str, "EventObjectDelete");
}

/*
** Registers all custom events and their handlers
** Caller must know what to input to handlers in event handling
*/

void		doom3d_register_custom_events(t_doom3d *app)
{
	app->custom_event_type = SDL_RegisterEvents(1);
	app->custom_event_handles = hash_map_create(NUM_CUSTOM_EVENTS);
	hash_map_add(app->custom_event_handles, event_delete_object,
		(void*)handle_object_deletion);
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
		ft_printf("ReceiveCustomEvent: %s\n", event_str);
		handle(app, event.user.data1, event.user.data2);
	}
}