/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_popup_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 15:34:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 17:05:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void		determine_menu_dimensions(t_button_menu *popup_menu,
					t_vec2 dims)
{
	int32_t		i;
	float		max_x_pos;
	float		max_y_pos;

	i = -1;
	max_x_pos = 0;
	max_y_pos = 0;
	while (++i < (int32_t)popup_menu->menu->num_buttons)
	{
		max_x_pos = popup_menu->menu->buttons[i]->pos[0] > max_x_pos ?
			popup_menu->menu->buttons[i]->pos[0] : max_x_pos;
		max_y_pos = popup_menu->menu->buttons[i]->pos[1] > max_y_pos ?
			popup_menu->menu->buttons[i]->pos[1] : max_y_pos;
	}
	max_x_pos += -popup_menu->menu->pos[0] +
		popup_menu->menu->buttons[0]->width + popup_menu->menu->space_between;
	max_y_pos += -popup_menu->menu->pos[1] +
		popup_menu->menu->buttons[0]->height + popup_menu->menu->space_between;
	dims[0] = max_x_pos;
	dims[1] = max_y_pos;
}

static void		set_background(t_surface *background,
					int32_t border_size, uint32_t background_color,
					uint32_t border_color)
{
	int32_t	y;
	int32_t	x;

	y = -1;
	while (++y < (int32_t)background->h)
	{
		x = -1;
		while (++x < (int32_t)background->w)
		{
			if ((y < border_size ||
					y >= (int32_t)background->h - border_size)
				|| (x < border_size ||
						x >= (int32_t)background->w - border_size))
				background->pixels[y * (int32_t)background->w + x] =
					border_color;
			else
				background->pixels[y * (int32_t)background->w + x] =
					background_color;
		}
	}
}

static void		button_popup_menu_clamp_position(t_button_menu *popup_menu)
{
	t_window		*window;

	window = popup_menu->menu->buttons[0]->window;
	while (popup_menu->pos[1] + popup_menu->background.h >
		window->framebuffer->height)
		popup_menu->pos[1]--;
	while (popup_menu->pos[1] < 0)
		popup_menu->pos[1]++;
	while (popup_menu->pos[0] + popup_menu->background.w >
		window->framebuffer->width)
		popup_menu->pos[0]--;
	while (popup_menu->pos[0] < 0)
		popup_menu->pos[0]++;
	button_group_update_position(popup_menu->menu, popup_menu->pos);
}

t_button_menu	*button_popup_menu_create(t_button_group *menu,
					t_vec2 pos, t_vec2 max_dimensions,
					uint32_t bg_and_border_color[2])
{
	t_button_menu	*popup_menu;
	t_vec2			dims;

	error_check(!(popup_menu = malloc(sizeof(*popup_menu))),
		"Failed to malloc popup menu");
	popup_menu->menu = menu;
	ml_vector2_copy(max_dimensions, popup_menu->max_dimensions);
	popup_menu->is_open = false;
	popup_menu->background_color = bg_and_border_color[0];
	popup_menu->border_color = bg_and_border_color[1];
	popup_menu->border_size = 2;
	determine_menu_dimensions(popup_menu, dims);
	popup_menu->background.w = (int32_t)(dims[0] + popup_menu->border_size);
	popup_menu->background.h = (int32_t)(dims[1] + popup_menu->border_size);
	error_check(!(popup_menu->background.pixels = malloc(sizeof(uint32_t) *
		popup_menu->background.w * popup_menu->background.h)),
		"Failed to malloc background");
	set_background(&popup_menu->background, popup_menu->border_size,
		popup_menu->background_color, popup_menu->border_color);
	ml_vector2_copy(pos, popup_menu->pos);
	button_popup_menu_clamp_position(popup_menu);
	return (popup_menu);
}

void			button_popup_menu_destroy(t_button_menu *popup_menu)
{
	button_group_destroy(popup_menu->menu);
	free(popup_menu->background.pixels);
	free(popup_menu);
}

void			button_popup_menu_render(t_button_menu *popup_menu)
{
	t_window	*window;

	if (popup_menu->menu->num_buttons == 0 || !popup_menu->is_open)
		return ;
	window = popup_menu->menu->buttons[0]->window;
	l3d_image_place(&(t_surface){.h = window->framebuffer->height,
		.w = window->framebuffer->width, .pixels = window->framebuffer->buffer},
		&popup_menu->background,
			(int32_t[2]){popup_menu->pos[0] - popup_menu->border_size,
			popup_menu->pos[1] - popup_menu->border_size}, 1.0);
	button_group_render(popup_menu->menu);
}
