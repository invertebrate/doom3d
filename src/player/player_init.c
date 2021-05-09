/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 14:11:09 by veilo             #+#    #+#             */
/*   Updated: 2021/05/09 20:11:50 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		player_transform_init(t_doom3d *app)
{
	ml_vector3_set(app->player.velocity, 0, 0, 0);
	ml_matrix4_id(app->player.rotation);
	ml_matrix4_id(app->player.inv_rotation);
	ml_matrix4_id(app->player.translation);
	ml_matrix4_id(app->player.inv_translation);
}

static void		player_attributes_init(t_doom3d *app)
{
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		app->player.speed = PLAYER_SPEED * 2;
		app->player.rot_speed = PLAYER_ROTATION_SPEED * 2;
	}
	else
	{
		app->player.speed = PLAYER_SPEED * 2;
		app->player.rot_speed = PLAYER_ROTATION_SPEED * 0.5;
	}
	app->player.rot_x = 0;
	app->player.rot_y = 0;
	app->player.player_height = PLAYER_HEIGHT * app->unit_size;
	app->player.fire_rate_per_sec = 4.0;
	app->player.aabb.size[0] = app->unit_size / 2.0;
	app->player.aabb.size[1] = app->player.player_height;
	app->player.aabb.size[2] = app->unit_size / 2.0;
	app->player.max_hp = 1000;
	app->player.hp = 1000;
	app->player.physics_state = physics_state_grounded;
	app->player.jump_force = PLAYER_JUMP_FORCE;
	app->player.can_fly = false;
}

static void		player_collider_init(t_doom3d *app)
{
	t_player	*player;

	player = &app->player;
	ml_vector3_copy(player->pos, player->collider.sphere.pos);
	ml_vector3_sub(player->collider.sphere.pos,
		(t_vec3){0.0, -0.5 * app->unit_size, 0.0}, player->collider.sphere.pos);
	ml_vector3_copy(player->up, player->collider.sphere.up);
	ml_vector3_copy(player->forward, player->collider.sphere.forward);
	player->collider.sphere.radius = 0.55 * app->unit_size;
	ft_memset(player->collider.rays, 0, sizeof(t_ray) * COLLIDER_RAY_TOTAL);
}

static void		player_ground_collider_init(t_doom3d *app)
{
	t_player	*player;

	player = &app->player;
	ml_vector3_copy(player->pos, player->collider_ground.cylinder.pos);
	ml_vector3_sub(player->collider_ground.cylinder.pos,
		(t_vec3){0.0, 0.0, 0.0}, player->collider_ground.cylinder.pos);
	ml_vector3_copy(player->up, player->collider_ground.cylinder.up);
	ml_vector3_copy(player->forward, player->collider_ground.cylinder.forward);
	player->collider_ground.cylinder.radius = 0.55 * app->unit_size;
	player->collider_ground.cylinder.height = 0.55 * app->unit_size;
	ft_memset(player->collider_ground.rays, 0,
		sizeof(t_ray) * COLLIDER_RAY_TOTAL);
}

void			player_init(t_doom3d *app, t_vec3 pos)
{
	ft_memset(&app->player, 0, sizeof(t_player));
	ft_memcpy(app->player.pos, pos, sizeof(t_vec3));
	ft_memcpy(app->player.forward, &(t_vec3){0, 0, Z_DIR}, sizeof(t_vec3));
	ft_memcpy(app->player.up, &(t_vec3){0, Y_DIR, 0}, sizeof(t_vec3));
	ft_memcpy(app->player.sideways, &(t_vec3){X_DIR, 0, 0}, sizeof(t_vec3));
	ft_memset(app->player.future_pos, 0, sizeof(t_vec3));
	player_attributes_init(app);
	player_transform_init(app);
	player_move(app);
	player_update_aabb(&app->player);
	SDL_GetRelativeMouseState(NULL, NULL);
	player_flashlight_init(app, &(app->player));
	player_collider_init(app);
	player_ground_collider_init(app);
	player_colliders_update(app);
}
