/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 20:45:21 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 12:38:29 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	transform_position_for_rendering(t_doom3d *app, t_vec3 pos)
{
	if (!app->settings.is_third_person)
	{
		ml_matrix4_mul_vec3(app->active_scene->main_camera->inv_translation,
			pos, pos);
		ml_matrix4_mul_vec3(app->active_scene->main_camera->inv_rotation,
			pos, pos);
	}
	else
	{
		ml_matrix4_mul_vec3(
			app->active_scene->third_person_camera->inv_translation, pos, pos);
		ml_matrix4_mul_vec3(
			app->active_scene->third_person_camera->inv_rotation, pos, pos);
	}	
}

t_camera	*get_render_camera(t_doom3d *app)
{
	t_camera	*camera;

	if (app->settings.is_third_person)
		camera = app->active_scene->third_person_camera;
	else
		camera = app->active_scene->main_camera;
	return (camera);
}
