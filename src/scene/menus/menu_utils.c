/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:51:29 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 18:26:29 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_surface			*convert_sdl_surface_to_t_surface(SDL_Surface *src)
{
	t_surface	*dst;

	error_check(!(dst = ft_calloc(sizeof(t_surface))),
		"Failed to malloc surface");
	error_check(!(dst->pixels = ft_calloc(sizeof(uint32_t) *
		src->w * src->h)), "Failed to malloc surface pixels");
	ft_memcpy(dst->pixels, src->pixels,
		sizeof(uint32_t) * src->w * src->h);
	dst->w = src->w;
	dst->h = src->h;
	return (dst);
}

static t_surface	*menu_button_surface(const char *option, TTF_Font *font)
{
	SDL_Surface	*tmp_surface;
	t_surface	*surface;

	tmp_surface = surface_from_font_shaded(
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 0, 0, 255}}, font);
	surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (surface);
}

static t_surface	*menu_button_down_surface(const char *option,
						TTF_Font *font)
{
	SDL_Surface	*tmp_surface;
	t_surface	*down_surface;

	tmp_surface = surface_from_font_shaded(
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 255, 255, 255}},
		font);
	down_surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (down_surface);
}

t_button_group		*button_menu_create(t_doom3d *app,
						t_button_menu_params menu_params)
{
	int32_t			i;
	t_button		**buttons;
	t_surface		*surfaces[menu_params.num_buttons];
	t_surface		*down_surfaces[menu_params.num_buttons];
	t_button_group	*menu;

	buttons = NULL;
	if (menu_params.num_buttons > 0)
		error_check(!(buttons = ft_calloc(sizeof(t_button*) *
			menu_params.num_buttons)), "Failed to malloc buttons");
	i = -1;
	while (++i < menu_params.num_buttons)
	{
		buttons[i] = button_create(app->window, i, menu_params.button_names[i]);
		surfaces[i] = menu_button_surface(menu_params.button_names[i],
			menu_params.button_font);
		down_surfaces[i] = menu_button_down_surface(menu_params.button_names[i],
			menu_params.button_font);
		button_set_texture(buttons[i], surfaces[i], down_surfaces[i]);
		button_set_handles(buttons[i], menu_params.on_click, NULL);
		button_set_handle_params(buttons[i], app, NULL);
	}
	menu = button_group_create(buttons, menu_params.num_buttons);
	return (menu);
}

void				scene_menus_destroy(t_scene *scene)
{
	int32_t		i;

	if (scene->num_button_menus > 0)
	{
		i = -1;
		while (++i < (int32_t)scene->num_button_menus)
			button_group_destroy(scene->menus[i]);
	}
	scene->num_button_menus = 0;
	free(scene->menus);
	scene->menus = NULL;
}
