/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_group_events.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 02:38:19 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:28:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void	button_selector_state_handle(t_button_group *button_group,
				t_mouse mouse, SDL_Event event, int32_t i)
{
	if (i == (int32_t)button_group->selected_index)
	{
		button_group->buttons[i]->is_down = true;
		button_group->buttons[i]->is_hovered = false;
	}
	else
		button_group->buttons[i]->is_down = false;
	if (button_is_down(button_group->buttons[i], mouse, event))
	{
		button_group->buttons[i]->is_down = true;
		button_group->buttons[i]->is_hovered = false;
	}
	else if (button_is_hovered(button_group->buttons[i], mouse, event)
		&& !button_group->buttons[i]->is_down)
	{
		button_group->buttons[i]->is_hovered = true;
		button_group->buttons[i]->is_down = false;
	}
	else
		button_group->buttons[i]->is_hovered = false;
}

/*
** Handle button groups events (click, hover, etc.)
** This should be hooked to the event loop
*/

void	button_group_events_handle(t_button_group *button_group,
			t_mouse mouse, SDL_Event event)
{
	int32_t		i;

	if (!button_group->is_active)
		return ;
	i = -1;
	if (!button_group->is_selector)
	{
		while (++i < (int32_t)button_group->num_buttons)
			button_state_handle(button_group->buttons[i], mouse, event);
	}
	else
	{
		while (++i < (int32_t)button_group->num_buttons)
		{
			if (button_is_clicked(button_group->buttons[i], mouse, event))
			{
				button_group->selected_index = i;
				if (button_group->buttons[i]->on_click != NULL)
					button_group->buttons[i]->on_click(button_group->buttons[i],
					button_group->buttons[i]->on_click_params);
			}
			button_selector_state_handle(button_group, mouse, event, i);
		}
	}
}
