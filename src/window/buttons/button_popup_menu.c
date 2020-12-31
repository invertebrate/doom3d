/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_popup_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:34:16 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/31 15:51:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

t_button_menu	*button_popup_menu_create(t_button_group *menu,
					t_vec2 pos, t_vec2 max_dimensions,
					uint32_t bacgrkound_color)
{
	t_button_menu	*popup_menu;
	t_vec2			button_rel_pos;

	error_check(!(popup_menu = malloc(sizeof(*popup_menu))),
		"Failed to malloc popup menu");
	popup_menu->menu = menu;
	ml_vector2_copy(max_dimensions, popup_menu->max_dimensions);
	ml_vector2_copy(pos, popup_menu->pos);
	ml_vector2_add(popup_menu->menu->pos, pos, button_rel_pos);
	button_group_update_position(popup_menu->menu, button_rel_pos);
	popup_menu->is_open = false;
	popup_menu->background_color = bacgrkound_color;
	popup_menu->border_color = 0xffffffff;
	return (popup_menu);
}

void			button_popup_menu_destroy(t_button_menu *popup_menu)
{
	button_group_destroy(popup_menu->menu);
	free(popup_menu);
}

void			button_group_menu_render(t_button_menu *popup_menu)
{
	t_window	*window;
	uint32_t	*background;
	t_vec2		dims;
	float		temp_dim;
	int32_t		i;

	if (popup_menu->menu->num_buttons == 0 || !popup_menu->is_open)
		return ;
	window = popup_menu->menu->buttons[0]->window;
	i = -1;
	dims[0] = 0;
	dims[1] = 0;
	while (++i < popup_menu->menu->num_buttons)
	{
		temp_dim = popup_menu->menu->buttons[i]->pos[0] +
			popup_menu->menu->buttons[i]->width;
		dims[0] = temp_dim > dims[0] ? temp_dim : dims[0];
		temp_dim = popup_menu->menu->buttons[i]->pos[1] +
			popup_menu->menu->buttons[i]->height;
		dims[1] = temp_dim > dims[1] ? temp_dim : dims[1];
	}
	// ToDo: Alloc background
	// Borders?
	// Place image
	// Render buttons on top
	// Then create a menu event handler...
}
