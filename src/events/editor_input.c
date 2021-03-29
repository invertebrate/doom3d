/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:36:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 17:42:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_editor_saving_inputs(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_TEXTINPUT)
	{
		doom3d_push_event(app, event_editor_save_type, event.text.text, NULL);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		doom3d_push_event(app, event_editor_end_save, NULL, NULL);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
	{
		doom3d_push_event(app, event_editor_save_type_backspace,
			event.text.text, NULL);
	}
}

void		handle_editor_selection_inputs(t_doom3d *app, SDL_Event event)
{
	if (app->editor.is_saving)
		return ;
	if (event.type == SDL_MOUSEBUTTONDOWN &&
		(app->mouse.state & SDL_BUTTON_LMASK))
	{
		if (app->mouse.x > app->window->editor_pos[0] && app->mouse.x <
				app->window->editor_pos[0] +
				app->window->editor_framebuffer->width &&
			app->mouse.y > app->window->editor_pos[1] && app->mouse.y <
				app->window->editor_pos[1] +
				app->window->editor_framebuffer->height)
			editor_select(app);
	}
	if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_TAB)
	{
		if (app->keyboard.state[SDL_SCANCODE_LCTRL])
			app->editor.editor_level--;
		else
			app->editor.editor_level++;
		if (app->editor.editor_level >= (int32_t)app->num_levels)
			app->editor.editor_level = 0;
		else if (app->editor.editor_level < 0)
			app->editor.editor_level = (int32_t)app->num_levels - 1;
		app->is_scene_reload = true;
		editor_init(app, app->editor.editor_level);
	}
}

