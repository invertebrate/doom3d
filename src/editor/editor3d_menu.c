/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/16 00:35:55 by ohakola          ###   ########.fr       */
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

static void			on_save_button_click(t_doom3d *app)
{
	(void)app;
	ft_printf("One day save when clicking this\n");
}

static void			on_editor_menu_button_click(t_button *self, void *params)
{
	t_doom3d	*app;

	app = params;
	if (self->id == 0)
	{
		app->next_scene_id = scene_id_main_menu;
		scene_next_select(app);
	}
	if (self->id == 1)
		on_save_button_click(app);
}

static void			set_editor_menu_button_surfaces(t_doom3d *app,
						const char *option,
						t_surface **surface, t_surface **down_surface)
{
	SDL_Surface	*tmp_surface;

	tmp_surface = surface_from_font(app->window,
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 0, 0, 255}}, app->window->main_font);
	*surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
	tmp_surface = surface_from_font(app->window,
		(t_text_params){.text = option, .blend_ratio = 1.0,
		.text_color = (SDL_Color){255, 255, 255, 255}},
		app->window->main_font);
	*down_surface = convert_sdl_surface_to_t_surface(tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

void				editor3d_menu_create(t_doom3d *app)
{
	int32_t		i;
	const char	*options[2];
	t_button	**buttons;
	t_surface	**surfaces;
	t_surface	**down_surfaces;

	options[0] = "Back";
	options[1] = "Save";
	error_check(!(buttons = malloc(sizeof(t_button*) * 2)), "!Merror");
	error_check(!(surfaces = malloc(sizeof(t_surface*) * 2)), "!Merror");
	error_check(!(down_surfaces = malloc(sizeof(t_surface*) * 2)), "!Merror");
	i = -1;
	while (++i < 2)
	{
		set_editor_menu_button_surfaces(app,
			options[i], &surfaces[i], &down_surfaces[i]);
		buttons[i] = button_create(app->window, i);
		button_set_texture(buttons[i], surfaces[i], down_surfaces[i]);
		button_set_handles(buttons[i], on_editor_menu_button_click, NULL);
		button_set_handle_params(buttons[i], app, NULL);
	}
	app->editor_menu_3d = button_group_create(buttons, 2);
	button_group_set_space_between(app->editor_menu_3d, 0);
	free(surfaces);
	free(down_surfaces);
}

