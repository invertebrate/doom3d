/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:36:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:38:50 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_editor_saving_input(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_TEXTINPUT)
	{
		push_custom_event(app, event_editor_save_type,
			ft_strdup(event.text.text), NULL);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
		push_custom_event(app, event_editor_end_save, NULL, NULL);
	else if (event.type == SDL_KEYDOWN
		&& event.key.keysym.sym == SDLK_BACKSPACE)
		push_custom_event(app, event_editor_save_type_backspace, NULL, NULL);
}

static void	handle_editor_selection_input(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (!app->editor.is_placing)
		{
			if ((app->mouse.state & SDL_BUTTON_LMASK)
				&& !editor_popup_menu_open(app))
				push_custom_event(app, event_editor_select, NULL, NULL);
			else if ((app->mouse.state & SDL_BUTTON_RMASK)
				&& app->editor.num_selected_objects > 0)
				push_custom_event(app, event_editor_deselect, NULL, NULL);
		}
		else
		{
			if (app->mouse.state & SDL_BUTTON_LMASK)
				push_custom_event(app, event_editor_end_placement, NULL, NULL);
			else if (app->mouse.state & SDL_BUTTON_RMASK)
				push_custom_event(app, event_editor_cancel_placement,
					NULL, NULL);
		}
	}
}

static void	handle_editor_key_input(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_TAB)
			push_custom_event(app, event_editor_level_switch, NULL, NULL);
		else if (event.key.keysym.sym == SDLK_EQUALS)
			push_custom_event(app,
				event_editor_increment_patrol_slot, NULL, NULL);
		else if (event.key.keysym.sym == SDLK_MINUS)
			push_custom_event(app,
				event_editor_decrement_patrol_slot, NULL, NULL);
		else if (event.key.keysym.sym == SDLK_v)
			push_custom_event(app,
				event_editor_toggle_lock_vertical, NULL, NULL);
		else if (event.key.keysym.sym == SDLK_SPACE)
			push_custom_event(app,
				event_editor_snap_to_grid, NULL, NULL);
		else if (!app->editor.is_saving
			&& (event.key.keysym.sym == SDLK_DELETE
				|| event.key.keysym.sym == SDLK_BACKSPACE))
			push_custom_event(app,
				event_editor_delete, NULL, NULL);
		else if (event.key.keysym.sym == SDLK_b)
			push_custom_event(app, event_editor_duplicate, NULL, NULL);
	}
}

void	handle_editor_input_events(t_doom3d *app, SDL_Event event)
{
	if (mouse_inside_editor_view(app))
		handle_editor_selection_input(app, event);
	if (app->editor.is_saving)
		handle_editor_saving_input(app, event);
	if (event.type == SDL_MOUSEWHEEL)
		push_custom_event(app, event_editor_zoom,
			(void*)(intptr_t)(-event.wheel.y * 10), NULL);
	handle_editor_key_input(app, event);
	handle_editor_key_input2(app, event);
}

t_bool	editor_popup_menu_open(t_doom3d *app)
{
	return (app->editor.editor_menu != NULL
		&& app->editor.editor_menu->is_open);
}
