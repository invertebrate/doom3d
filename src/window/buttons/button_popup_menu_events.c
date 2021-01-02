/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_popup_menu_events.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 16:05:06 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 16:41:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	button_popup_menu_events_handle(t_button_menu *button_menu,
			t_mouse mouse, SDL_Event event)
{
	if (mouse.x >= button_menu->pos[0] &&
		mouse.x < button_menu->pos[0] + button_menu->background.w &&
		mouse.y >= button_menu->pos[1] &&
		mouse.y < button_menu->pos[1] + button_menu->background.h)
		button_group_events_handle(button_menu->menu, mouse, event);
	else if ((mouse.state & SDL_BUTTON_LMASK))
		button_menu->is_open = false;
}
