/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:36:14 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/30 23:13:27 by ohakola          ###   ########.fr       */
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
		ft_memcpy(app->editor.editor_filename, app->editor.editor_savename,
			ft_strlen(app->editor.editor_savename));
		save_map(app);
		ft_printf("Saved %s\n", app->editor.editor_filename);
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
}

