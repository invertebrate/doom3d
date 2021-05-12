/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_input2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 18:34:02 by veilo             #+#    #+#             */
/*   Updated: 2021/05/12 10:55:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_editor_key_input2(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_p)
			push_custom_event(app, event_editor_flip_lights, NULL, NULL);
		if (event.key.keysym.sym == SDLK_c)
			push_custom_event(app, event_object_set_shading_not_cull,
				NULL, NULL);
	}
}

static void	disable_menu(t_button_group *menu)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)menu->num_buttons)
		menu->buttons[i]->is_active = false;
}

static void	enable_menu(t_button_group *menu)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)menu->num_buttons)
		menu->buttons[i]->is_active = true;
}

void	disable_editor_menus_on_save(t_doom3d *app)
{
	int32_t	i;

	if (app->active_scene->scene_id != scene_id_editor3d)
		return ;
	i = -1;
	while (++i < 4)
		disable_menu(app->active_scene->menus[i]);
	app->active_scene->menus[0]->buttons[0]->is_active = true;
	app->active_scene->menus[0]->buttons[1]->is_active = true;
}

void	enable_editor_menus_after_save(t_doom3d *app)
{
	int32_t	i;

	if (app->active_scene->scene_id != scene_id_editor3d)
		return ;
	i = -1;
	while (++i < 4)
		enable_menu(app->active_scene->menus[i]);
}
