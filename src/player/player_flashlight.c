/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo     <veilo@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:47:40 by veilo             #+#    #+#             */
/*   Updated: 2021/04/07 21:11:58 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom3d.h"

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
	fl->cone.radius	= 6.0 * app->unit_size;
	fl->intensity = 3.0;

}

void		player_flashlight_update(t_player *player)
{
	t_flashlight	*fl;

	fl = &(player->flashlight);
	ml_vector3_copy(player->pos, fl->cone.apex);
	ml_matrix4_mul_vec3(player->inv_translation, fl->cone.apex, fl->cone.apex);
	ml_matrix4_mul_vec3(player->inv_rotation, fl->cone.apex, fl->cone.apex);
	ml_vector3_set(fl->cone.dir, 0.0, 0.0, Z_DIR);
}