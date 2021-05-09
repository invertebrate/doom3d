/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:29:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

/*
** Checks whether button is down by sdl event and mouse state
*/

t_bool	button_is_down(t_button *button, t_mouse mouse,
			SDL_Event event)
{
	t_bool		res;

	if (!button->is_active)
		return (false);
	res = false;
	if (mouse.x >= button->pos[0]
		&& mouse.x < button->pos[0] + button->width
		&& mouse.y >= button->pos[1]
		&& mouse.y < button->pos[1] + button->height)
	{
		if ((event.type == SDL_MOUSEBUTTONDOWN
				&& event.button.button == SDL_BUTTON_LMASK)
			|| (mouse.state & SDL_BUTTON_LMASK))
			return (true);
	}
	return (res);
}

/*
** Checks whether button is clicked by sdl event and mouse state
*/

t_bool	button_is_clicked(t_button *button, t_mouse mouse,
			SDL_Event event)
{
	t_bool		res;

	if (!button->is_active)
		return (false);
	res = false;
	if (mouse.x >= button->pos[0]
		&& mouse.x < button->pos[0] + button->width
		&& mouse.y >= button->pos[1]
		&& mouse.y < button->pos[1] + button->height)
	{
		if (event.type == SDL_MOUSEBUTTONUP
			&& event.button.button == SDL_BUTTON_LMASK)
			return (true);
	}
	return (res);
}

/*
** Checks whether button is hovered by sdl event and mouse state
*/

t_bool	button_is_hovered(t_button *button, t_mouse mouse,
			SDL_Event event)
{
	t_bool		res;

	if (!button->is_active)
		return (false);
	res = false;
	if (mouse.x >= button->pos[0]
		&& mouse.x < button->pos[0] + button->width
		&& mouse.y >= button->pos[1]
		&& mouse.y < button->pos[1] + button->height)
	{
		if (!button_is_clicked(button, mouse, event)
			&& !button_is_down(button, mouse, event))
			return (true);
	}
	return (res);
}

/*
** Handle button state with sdl event and mouse state
*/

void	button_state_handle(t_button *button, t_mouse mouse,
			SDL_Event event)
{
	if (button_is_clicked(button, mouse, event))
	{
		if (button->on_click != NULL)
			button->on_click(button, button->on_click_params);
		button->is_down = false;
		button->is_hovered = true;
	}
	else if (button_is_hovered(button, mouse, event))
	{
		if (button->on_hover != NULL)
			button->on_hover(button, button->on_hover_params);
		button->is_hovered = true;
		button->is_down = false;
	}
	else if (button_is_down(button, mouse, event))
	{
		button->is_down = true;
		button->is_hovered = false;
	}
	else
	{
		button->is_down = false;
		button->is_hovered = false;
	}
}
