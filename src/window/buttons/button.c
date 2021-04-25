/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 17:54:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

/*
** Create new button with pointer to a window and id (index)
*/

t_button		*button_create(t_window *window, uint32_t id, const char *text)
{
	t_button		*button;

	error_check(!(button = ft_calloc(sizeof(t_button))),
		"Failed to malloc btn");
	button->id = id;
	button->window = window;
	button->text = text;
	button->is_active = true;
	return (button);
}

/*
** Destroy button
*/

void			button_destroy(t_button *button)
{
	if (button->texture)
	{
		free(button->texture->pixels);
		free(button->texture);
	}
	if (button->texture_down)
	{
		free(button->texture_down->pixels);
		free(button->texture_down);
	}
	free(button);
	button = NULL;
}
