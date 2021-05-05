/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:22:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

/*
** Set texture of a button
*/

void	button_set_texture(t_button *button, t_surface *texture,
			t_surface *texture_down)
{
	error_check(!texture, "No texture given, invalid button use");
	button->texture = texture;
	button->texture_down = texture_down;
	button->width = texture->w;
	button->height = texture->h;
}

/*
** Set event handles for a button
*/

void	button_set_handles(t_button *button,
		void (*on_click)(t_button *, void *),
		void (*on_hover)(t_button *, void *))
{
	button->on_click = on_click;
	button->on_hover = on_hover;
}

/*
** Set params to which event handles can access on a button
*/

void	button_set_handle_params(t_button *button,
			void *on_click_params,
			void *on_hover_params)
{
	button->on_click_params = on_click_params;
	button->on_hover_params = on_hover_params;
}

/*
** Update button render position
*/

void	button_update_position(t_button *button, t_vec2 pos)
{
	ml_vector2_copy(pos, button->pos);
}

/*
** Render button
*/

void	button_render(t_button *button)
{
	int32_t		pos[2];
	float		blend;
	t_surface	*texture;

	if (!button->texture)
		return ;
	pos[0] = button->pos[0];
	pos[1] = button->pos[1];
	blend = 1.0;
	if (button->is_hovered)
		blend = 0.5;
	texture = button->texture;
	if (button->is_down)
		texture = button->texture_down;
	l3d_image_place(
		&(t_surface){
		.h = button->window->framebuffer->height,
		.w = button->window->framebuffer->width,
		.pixels = button->window->framebuffer->buffer},
		texture, pos, blend);
}
