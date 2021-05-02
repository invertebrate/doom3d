/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:00:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 18:03:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Update camera with player's location
*/

void			update_camera(t_camera *camera, float dims_focal_length[3],
					t_vec3 forward_up_sideways[3], t_vec3 pos)
{
	camera->near_clip = Z_DIR * NEAR_CLIP_DIST;
	camera->far_clip = Z_DIR * FAR_CLIP_DIST;
	ml_vector3_set(camera->screen.origin, 0, 0, dims_focal_length[2]);
	ml_vector3_set(camera->screen.normal, 0, 0, -Z_DIR);
	set_camera_viewbox(camera, dims_focal_length, forward_up_sideways, pos);
}

void			update_player_camera(t_doom3d *app)
{
	t_vec3	forward_up_sideways[3];
	float	dims[2];
	float	focal_length;

	dims[0] = app->window->framebuffer->width / 2.0;
	dims[1] = app->window->framebuffer->height / 2.0;
	focal_length = Z_DIR * app->window->framebuffer->width * 0.7;
	ml_vector3_copy(app->player.forward, forward_up_sideways[0]);
	ml_vector3_copy(app->player.up, forward_up_sideways[1]);
	ml_vector3_copy(app->player.sideways, forward_up_sideways[2]);
	update_camera(app->active_scene->main_camera,
		(float [3]){dims[0], dims[1], focal_length},
		forward_up_sideways, app->player.pos);
}
