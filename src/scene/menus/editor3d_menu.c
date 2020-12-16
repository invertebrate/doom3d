/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 00:07:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/16 16:53:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void			on_save(t_doom3d *app)
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
		on_save(app);
}

void				editor3d_menu_create(t_doom3d *app)
{
	const char	*options[2];

	options[0] = "Back";
	options[1] = "Save";
	app->active_scene->menu = button_menu_create(app, options, 2,
		on_editor_menu_button_click);
}

