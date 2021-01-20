/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/20 14:29:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			player_update_aabb(t_player *player)
{
	player->aabb.xyz_min[0] = player->pos[0] - player->aabb.size[0] / 2.0;
	player->aabb.xyz_min[1] = player->pos[1] - player->aabb.size[1] / 2.0;
	player->aabb.xyz_min[2] = player->pos[2] - player->aabb.size[2] / 2.0;
	player->aabb.xyz_max[0] = player->pos[0] + player->aabb.size[0] / 2.0;
	player->aabb.xyz_max[1] = player->pos[1] + player->aabb.size[1] / 2.0;
	player->aabb.xyz_max[2] = player->pos[2] + player->aabb.size[2] / 2.0;
	ml_vector3_copy(player->pos, player->aabb.center);
}

void			player_init(t_doom3d *app, t_vec3 pos)
{
	ft_memset(&app->player, 0, sizeof(t_player));
	ft_memcpy(app->player.pos, pos, sizeof(t_vec3));
	ft_memcpy(app->player.forward, &(t_vec3){0, 0, Z_DIR}, sizeof(t_vec3));
	ft_memcpy(app->player.up, &(t_vec3){0, Y_DIR, 0}, sizeof(t_vec3));
	ft_memcpy(app->player.sideways, &(t_vec3){X_DIR, 0, 0}, sizeof(t_vec3));
	app->player.speed = PLAYER_SPEED;
	app->player.rot_speed = PLAYER_ROTATION_SPEED;
	app->player.rot_x = 0;
	app->player.rot_y = 0;
	app->player.player_height = 1.75 * app->unit_size;
	app->player.fire_rate_per_sec = 4.0;
	app->player.aabb.size[0] = app->unit_size / 2.0;
	app->player.aabb.size[1] = app->player.player_height;
	app->player.aabb.size[2] = app->unit_size / 2.0;
	app->player.hp = 100; //test
	app->player.flying = false;
	app->player.jump_force = app->unit_size * 1 / 10;
	ml_vector3_set(app->player.velocity, 0, 0, 0);
	ml_matrix4_id(app->player.rotation);
	ml_matrix4_id(app->player.inv_rotation);
	ml_matrix4_id(app->player.translation);
	ml_matrix4_id(app->player.inv_translation);
	player_move(app, move_forward, 0.0);
	player_update_aabb(&app->player);
}
