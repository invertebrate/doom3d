/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:51:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 22:51:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_window_resize(t_doom3d *app, uint32_t width,
								uint32_t height)
{
	app->settings.width = width;
	app->settings.height = height;
	window_resize(app->window, width, height);
}

void	handle_scene_change(t_doom3d *app, t_scene_id scene_id)
{
	int32_t		fd;
	char		filename[128];

	if (scene_id == scene_id_editor3d)
	{
		if (app->is_asset_load)
		{
			ft_sprintf(filename, "assets/models/box.obj");
			fd = open(filename, O_RDONLY);
			if (fd == -1)
			{
				notify_user(app, (t_notification){.message
					= "To use editor, you must launch the app so that the "
					"assets folder is next to the executable",
					.time = 4000, .type = notification_type_info});
				close(fd);
				return ;
			}
		}
	}
	app->next_scene_id = scene_id;
}

void	handle_scene_reload(t_doom3d *app)
{
	app->is_scene_reload = true;
}
