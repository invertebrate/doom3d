/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:51:29 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/29 20:45:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Create button menu
*/

t_button_group	*button_menu_create(t_doom3d *app,
					t_button_menu_params menu_params)
{
	int32_t			i;
	t_button		**buttons;
	t_button_group	*menu;

	buttons = NULL;
	if (menu_params.num_buttons > 0)
		error_check(!(buttons = ft_calloc(sizeof(t_button *)
					* menu_params.num_buttons)), "Failed to malloc buttons");
	i = -1;
	while (++i < menu_params.num_buttons)
	{
		buttons[i] = button_create(app->window, i, menu_params.button_names[i]);
		button_set_texture(buttons[i],
			menu_button_surface(menu_params.button_names[i],
				menu_params.button_font),
			menu_button_down_surface(menu_params.button_names[i],
				menu_params.button_font));
		button_set_handles(buttons[i], menu_params.on_click, NULL);
		button_set_handle_params(buttons[i], app, NULL);
	}
	menu = button_group_create(buttons, menu_params.num_buttons, false);
	return (menu);
}

/*
** Create shaded button menu (better looking, but with background)
*/

t_button_group	*button_menu_create_shaded(t_doom3d *app,
					t_button_menu_params pms)
{
	int32_t			i;
	t_button		**buttons;
	t_button_group	*menu;

	buttons = NULL;
	if (pms.num_buttons > 0)
		error_check(!(buttons = ft_calloc(sizeof(t_button *)
					* pms.num_buttons)), "Failed to malloc buttons");
	i = -1;
	while (++i < pms.num_buttons)
	{
		buttons[i] = button_create(app->window, i, pms.button_names[i]);
		button_set_texture(buttons[i],
			menu_button_surface_shaded(pms.button_names[i],
				pms.button_font),
			menu_button_down_surface_shaded(pms.button_names[i],
				pms.button_font));
		button_set_handles(buttons[i], pms.on_click, NULL);
		button_set_handle_params(buttons[i], app, NULL);
	}
	menu = button_group_create(buttons, pms.num_buttons, false);
	return (menu);
}

/*
** Destroy scene menus
*/

void	scene_menus_destroy(t_scene *scene)
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
