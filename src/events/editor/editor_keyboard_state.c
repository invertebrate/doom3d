/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_keyboard_state.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:41:49 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 02:37:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	wasd_is_pressed(t_doom3d *app)
{
	return (app->keyboard.state[SDL_SCANCODE_W] ||
		app->keyboard.state[SDL_SCANCODE_A] ||
		app->keyboard.state[SDL_SCANCODE_S] ||
		app->keyboard.state[SDL_SCANCODE_D]);
}

static void		handle_wasd_input(t_doom3d *app)
{
	int32_t	shift;

	shift = app->keyboard.state[SDL_SCANCODE_LSHIFT] ? 5 : 1;
	if (app->keyboard.state[SDL_SCANCODE_W])
		push_custom_event(app, event_editor_move_view_forward,
			(void*)(intptr_t)shift, NULL);
	if (app->keyboard.state[SDL_SCANCODE_A])
		push_custom_event(app, event_editor_move_view_sideways,
			(void*)(intptr_t)-shift, NULL);
	if (app->keyboard.state[SDL_SCANCODE_S])
		push_custom_event(app, event_editor_move_view_forward,
			(void*)(intptr_t)-shift, NULL);
	if (app->keyboard.state[SDL_SCANCODE_D])
		push_custom_event(app, event_editor_move_view_sideways,
			(void*)(intptr_t)shift, NULL);
}

void			handle_editor_keyboard_state_input(t_doom3d *app)
{
	handle_wasd_input(app);
	if (wasd_is_pressed(app))
		app->editor.is_moving = true;
	else
		app->editor.is_moving = false;
	handle_editor_transform_input(app);
}
