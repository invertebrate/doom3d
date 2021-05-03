/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_flashlight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:47:40 by veilo             #+#    #+#             */
/*   Updated: 2021/05/03 15:36:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		player_flashlight_init(t_doom3d *app, t_player *player)
{
	t_flashlight	*fl;

	if (app->active_scene->scene_id != scene_id_main_game)
	{
		player->flashlight.enabled = false;
		return ;
	}
	player->flashlight.enabled = true;
	player->flashlight.active = true;
	fl = &(player->flashlight);
	fl->light_color = L3D_COLOR_WHITE;
	ml_vector3_copy(player->pos, fl->cone.apex);
	ml_vector3_copy(player->forward, fl->cone.dir);
	fl->cone.height = 18.0 * app->unit_size;
	fl->cone.radius = 6.0 * app->unit_size;
	fl->intensity = 3.0;
}

void		player_flashlight_update(t_doom3d *app)
{
	t_flashlight	*fl;

	fl = &(app->player.flashlight);
	ml_vector3_copy(app->player.pos, fl->cone.apex);
	transform_position_for_rendering(app, fl->cone.apex);
	ml_vector3_set(fl->cone.dir, 0.0, 0.0, Z_DIR);
}
