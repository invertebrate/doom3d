/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:40:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 16:04:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Trigger custom events that aren't related to menu clicks or game interaction,
** like exiting or esc or setting to full screen, or disabling debug info
*/

void			handle_control_flow_events(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_QUIT)
	{
		LOG_INFO("Quit input");
		push_custom_event(app, event_quit, NULL, NULL);
	}
	if (!SDL_IsTextInputActive() && !app->editor.is_saving)
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			push_custom_event(app, event_quit, NULL, NULL);
		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_n)
				push_custom_event(app, event_toggle_normal_map_mode,
					NULL, NULL);
			if (event.key.keysym.sym == SDLK_p &&
				app->active_scene->scene_id == scene_id_main_game)
				push_custom_event(app, event_toggle_pause_game, NULL, NULL);
			if (event.key.keysym.sym == SDLK_u)
				push_custom_event(app, event_toggle_debug_mode, NULL, NULL);
			if (event.key.keysym.sym == SDLK_f)
				push_custom_event(app, event_toggle_fullscreen, NULL, NULL);
		}
	}
}
