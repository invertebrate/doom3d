/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_person.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:40:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 12:38:10 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_toggle_third_person(t_doom3d *app)
{
	const char	*view_str;

	if (app->active_scene->scene_id == scene_id_main_game
		&& !app->active_scene->is_paused)
		app->settings.is_third_person = !app->settings.is_third_person;
	if (app->settings.is_debug)
	{
		if (app->settings.is_third_person)
			view_str = "3rd Person";
		else
			view_str = "1st Person";
		LOG_INFO("View now is: %s", view_str);
	}
}

void	handle_third_person_zoom(t_doom3d *app, int32_t zoom_amount)
{
	if (!app->settings.is_third_person)
		return ;
	app->active_scene->third_person_camera_distance
		+= zoom_amount * 0.5 * app->unit_size;
	if (app->active_scene->third_person_camera_distance <= app->unit_size * 1)
		app->active_scene->third_person_camera_distance = app->unit_size * 1;
	if (app->active_scene->third_person_camera_distance > app->unit_size * 15)
		app->active_scene->third_person_camera_distance = app->unit_size * 15;
}
