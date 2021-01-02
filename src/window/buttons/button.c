/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/02 17:32:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

t_button		*button_create(t_window *window, uint32_t id, const char *text)
{
	t_button		*button;

	error_check(!(button = malloc(sizeof(t_button))), "Failed to malloc btn");
	ft_memset(button, 0, sizeof(t_button));
	button->id = id;
	button->window = window;
	if (text != NULL)
		button->text = ft_strdup(text);
	return (button);
}

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
	if (button->text)
		ft_strdel(&button->text);
	free(button);
	button = NULL;
}
