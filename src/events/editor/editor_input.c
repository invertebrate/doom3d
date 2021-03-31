/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:36:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 15:04:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_editor_saving_inputs(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_TEXTINPUT)
	{
		doom3d_push_event(app, event_editor_save_type, event.text.text, NULL);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		doom3d_push_event(app, event_editor_end_save, NULL, NULL);
	}
	else if (event.type == SDL_KEYDOWN &&
		event.key.keysym.sym == SDLK_BACKSPACE)
	{
		doom3d_push_event(app, event_editor_save_type_backspace,
			event.text.text, NULL);
	}
}

static void	handle_editor_selection_inputs(t_doom3d *app, SDL_Event event)
{
	if (app->editor.is_saving)
		return ;
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (!app->editor.is_placing)
		{
			if (app->mouse.state & SDL_BUTTON_LMASK)
				doom3d_push_event(app, event_editor_select, NULL, NULL);
			else if ((app->mouse.state & SDL_BUTTON_RMASK) &&
				app->editor.num_selected_objects > 0)
				doom3d_push_event(app, event_editor_deselect, NULL, NULL);
		}
		else
		{
			if (app->mouse.state & SDL_BUTTON_LMASK)
				doom3d_push_event(app, event_editor_end_placement, NULL, NULL);
			else if (app->mouse.state & SDL_BUTTON_RMASK)
				doom3d_push_event(app, event_editor_cancel_placement,
					NULL, NULL);
		}
	}
}

static void	handle_editor_key_inputs(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_TAB)
			doom3d_push_event(app, event_editor_level_switch, NULL, NULL);
		else if (event.key.keysym.sym == SDLK_EQUALS)
			doom3d_push_event(app,
				event_editor_increment_patrol_slot, NULL, NULL);
		else if (event.key.keysym.sym == SDLK_MINUS)
			doom3d_push_event(app,
				event_editor_decrement_patrol_slot, NULL, NULL);
	}
}

void		handle_editor_input_events(t_doom3d *app, SDL_Event event)
{
	t_vec3	dir;

	if (mouse_inside_editor_view(app))
		handle_editor_selection_inputs(app, event);
	handle_editor_saving_inputs(app, event);
	if (event.type == SDL_MOUSEWHEEL)
	{
		ml_vector3_mul(app->player.forward, -event.wheel.y * 10.0, dir);
		ml_vector3_add(app->player.velocity, dir, app->player.velocity);
	}
	handle_editor_key_inputs(app, event);
}

t_bool		editor_popup_menu_open(t_doom3d *app)
{
	return (app->editor.editor_menu != NULL &&
			app->editor.editor_menu->is_open);
}
