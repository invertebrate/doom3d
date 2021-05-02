/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_person.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:40:03 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 19:50:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		handle_toggle_third_person(t_doom3d *app)
{
	const char	*view_str;

	if (app->active_scene->scene_id == scene_id_main_game &&
		!app->active_scene->is_paused)
		app->is_third_person = !app->is_third_person;
	if (app->is_debug)
	{
		if (app->is_third_person)
			view_str = "3rd Person";
		else
			view_str = "1st Person";
		LOG_INFO("View now is: %s", view_str);
	}
}
