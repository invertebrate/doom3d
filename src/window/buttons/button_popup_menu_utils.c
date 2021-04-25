/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_popup_menu_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:55:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 17:57:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

/*
** Destroy a popup menu
*/

void			button_popup_menu_destroy(t_button_menu *popup_menu)
{
	if (popup_menu->menu)
		button_group_destroy(popup_menu->menu);
	free(popup_menu->background.pixels);
	free(popup_menu);
}

/*
** Render a popup menu
*/

void			button_popup_menu_render(t_window *window,
					t_button_menu *popup_menu)
{
	int32_t		pos_x;
	int32_t		pos_y;

	if (!popup_menu->is_open)
		return ;
	pos_x = popup_menu->pos[0] - popup_menu->border_size;
	pos_y = popup_menu->pos[1] - popup_menu->border_size;
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width, .pixels = window->framebuffer->buffer},
		&popup_menu->background, (int32_t[2]){pos_x, pos_y}, 1.0);
	if (popup_menu->menu)
		button_group_render(popup_menu->menu);
}
