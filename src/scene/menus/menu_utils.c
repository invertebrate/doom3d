/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:51:29 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/17 16:06:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_surface			*convert_sdl_surface_to_t_surface(SDL_Surface *src)
{
	t_surface	*dst;

	error_check(!(dst = malloc(sizeof(t_surface))),
		"Failed to malloc surface");
	error_check(!(dst->pixels = malloc(sizeof(uint32_t) *
		src->w * src->h)), "Failed to malloc surface pixels");
	ft_memcpy(dst->pixels, src->pixels,
		sizeof(uint32_t) * src->w * src->h);
	dst->w = src->w;
	dst->h = src->h;
	return (dst);
}

static t_surface		*menu_button_surface(t_doom3d *app,
							const char *option)
{
	SDL_Surface	*tmp_surface;
	t_surface	*surface;

	tmp_surface = surface_from_font(
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 0, 0, 255}}, app->window->main_font);
	surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (surface);
}

static t_surface		*menu_button_down_surface(t_doom3d *app,
							const char *option)
{
	SDL_Surface	*tmp_surface;
	t_surface	*down_surface;

	tmp_surface = surface_from_font(
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 255, 255, 255}},
		app->window->main_font);
	down_surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (down_surface);
}

t_button_group		*button_menu_create(t_doom3d *app,
						const char **options, int32_t num_buttons,
						void (*on_click)(t_button *, void *))
{
	int32_t			i;
	t_button		**buttons;
	t_surface		*surfaces[num_buttons];
	t_surface		*down_surfaces[num_buttons];
	t_button_group	*menu;

	error_check(!(buttons = malloc(sizeof(t_button*) * num_buttons)),
		"Failed to malloc buttons");
	i = -1;
	while (++i < num_buttons)
	{
		buttons[i] = button_create(app->window, i);
		surfaces[i] = menu_button_surface(app, options[i]);
		down_surfaces[i] = menu_button_down_surface(app, options[i]);
		button_set_texture(buttons[i], surfaces[i], down_surfaces[i]);
		button_set_handles(buttons[i], on_click, NULL);
		button_set_handle_params(buttons[i], app, NULL);
	}
	menu = button_group_create(buttons, num_buttons);
	return (menu);
}
