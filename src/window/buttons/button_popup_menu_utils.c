/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_popup_menu_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:55:12 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 19:30:53 by ohakola          ###   ########.fr       */
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

static void		clamp_popup_menu_position_for_large_height(t_button_menu
					*popup_menu, t_mouse *mouse)
{
	t_window		*window;

	window = popup_menu->menu->buttons[0]->window;
	if (mouse->y > window->framebuffer->height / 2)
	{
		while (popup_menu->pos[1] + popup_menu->background.h >
		window->framebuffer->height)
			popup_menu->pos[1]--;
	}
	if (mouse->y <= window->framebuffer->height / 2)	
	{
		while (popup_menu->pos[1] < 0)
			popup_menu->pos[1]++;
	}
}

void			button_popup_menu_clamp_position_to_window(
					t_button_menu *popup_menu, t_mouse *mouse)
{
	t_window		*window;
	t_vec2			buttons_pos;

	if (!popup_menu->menu)
		return ;
	window = popup_menu->menu->buttons[0]->window;
	while (popup_menu->pos[1] + popup_menu->background.h >
		window->framebuffer->height)
		popup_menu->pos[1]--;
	while (popup_menu->pos[1] < 0)
		popup_menu->pos[1]++;
	if (mouse &&
		(int32_t)popup_menu->background.h > window->framebuffer->height)
		clamp_popup_menu_position_for_large_height(popup_menu, mouse);
	while (popup_menu->pos[0] + popup_menu->background.w >
		window->framebuffer->width)
		popup_menu->pos[0]--;
	while (popup_menu->pos[0] < 0)
		popup_menu->pos[0]++;
	ml_vector2_add(popup_menu->pos,
		(t_vec2){popup_menu->border_size + popup_menu->padding,
			popup_menu->border_size + popup_menu->padding}, buttons_pos);
	button_group_update_position(popup_menu->menu, buttons_pos);
}
