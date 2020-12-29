/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 19:36:14 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/29 15:27:28 by ohakola          ###   ########.fr       */
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
		length = ft_strlen(app->editor.editor_filename);
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

void		handle_editor_transform(t_doom3d *app, SDL_Event event)
{
	if (app->editor.is_saving || !app->editor.selected_object)
		return ;
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP)
			l3d_3d_object_translate(app->editor.selected_object,
				0, 0, 0.1 * app->unit_size);
		else if (event.key.keysym.sym == SDLK_RIGHT)
			l3d_3d_object_translate(app->editor.selected_object,
				 0.1 * app->unit_size, 0, 0);
		else if (event.key.keysym.sym == SDLK_DOWN)
			l3d_3d_object_translate(app->editor.selected_object,
				0, 0, -0.1 * app->unit_size);
		else if (event.key.keysym.sym == SDLK_LEFT)
			l3d_3d_object_translate(app->editor.selected_object,
				-0.1 * app->unit_size, 0, 0);
	}
}
