/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:36:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/07 15:30:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_editor_saving(t_doom3d *app, SDL_Event event)
{
	int32_t		length;

	if (event.type == SDL_TEXTINPUT)
	{
		app->editor.is_saved = false;
		ft_strcat(app->editor.editor_savename, event.text.text);
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		SDL_StopTextInput();
		app->editor.is_saving = false;
		if (!find_one_object_by_type(app, object_type_trigger,
			trigger_player_start) ||
			!find_one_object_by_type(app, object_type_trigger,
			trigger_player_end))
		{
			doom3d_notification_add(app,
				"You need to add start and end before saving!");
			return ;
		}
		ft_memcpy(app->editor.editor_filename, app->editor.editor_savename,
			ft_strlen(app->editor.editor_savename));
		editor_triggers_unhighlight(app);
		save_map(app);
		editor_triggers_highlight(app);
		doom3d_notification_add(app, "Saved level!");
		app->editor.is_saved = true;
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
	{
		app->editor.is_saved = false;
		length = ft_strlen(app->editor.editor_savename);
		if (length > 0)
			app->editor.editor_savename[length - 1] = '\0';
	}
}

void		handle_editor_selection(t_doom3d *app, SDL_Event event)
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

