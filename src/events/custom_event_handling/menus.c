/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:51:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 02:16:49 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_window_resize(t_doom3d *app, uint32_t width,
								uint32_t height)
{
	app->settings.width = width;
	app->settings.height = height;
	window_resize(app->window, width, height);
}

void		handle_scene_change(t_doom3d *app, t_scene_id scene_id)
{
	app->next_scene_id = scene_id;
}

void		handle_scene_reload(t_doom3d *app)
{
	app->is_scene_reload = true;
}

void		handle_quit(t_doom3d *app)
{
	app->is_running = false;
}
