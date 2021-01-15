/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/15 18:57:35 by ahakanen         ###   ########.fr       */
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
	ml_matrix4_id(app->player.rotation);
	ml_matrix4_id(app->player.inv_rotation);
	ml_matrix4_id(app->player.translation);
	ml_matrix4_id(app->player.inv_translation);
	player_move(app, move_forward, 0.0);
	player_update_aabb(&app->player);
	app->player.hp = 100; //test
	app->player.flying = false;
	app->player.jump_force = app->unit_size * 1 / 10;
}

static void		shoot_shotgun(t_doom3d *app, t_vec3 origin)
{
	t_vec3			add;
	t_vec3			target;
	t_vec3			add_sideways;
	t_vec3			add_upways;
	t_vec3			dir;
	int32_t			i;

	ml_vector3_mul(app->player.forward, app->unit_size, add);
	i = -1;
	while (++i < 6)
	{
		ml_vector3_add(app->player.pos, add, target);
		ml_vector3_mul(app->player.sideways,
			(0.15 * l3d_rand_d() - 0.075) * app->unit_size,
			add_sideways);
		ml_vector3_mul(app->player.up,
			(0.15 * l3d_rand_d() - 0.075) * app->unit_size,
			add_upways);
		ml_vector3_add(target, add_sideways, target);
		ml_vector3_add(target, add_upways, target);
		ml_vector3_sub(target, origin, dir);
		player_shoot_ray(app, origin, dir);
	}
}

/*
** 	Clicking shoots right away. Else, fired according to fire rate
** // ToDo: Add various weapons & fire rates etc.
** // ToDo: Add bullet temp objects to hit surface
*/

void			player_shoot(t_doom3d *app, uint32_t curr_time)
{
	t_vec3			origin;
	t_vec3			add;
	static uint32_t	prev_shot_time;

	if (prev_shot_time != 0 && (float)(curr_time - prev_shot_time) / 1000.0 <
		(1.0 / app->player.equipped_weapon->fire_rate))
		return ;
	if (app->player.equipped_weapon->ammo > 0)
		set_player_shoot_frame(app);
	else if (app->player.equipped_weapon->ammo == 0)
	{
		ft_printf("Out of ammo\n");
		set_player_default_frame(app);
		return ;
	}
	prev_shot_time = SDL_GetTicks();
	ml_vector3_mul(app->player.forward, NEAR_CLIP_DIST, add);
	ml_vector3_add(app->player.pos, add, origin);
	if (app->player.equipped_weapon->id == weapon_fist ||
		app->player.equipped_weapon->id == weapon_glock)
		player_shoot_ray(app, origin, app->player.forward);
	else if (app->player.equipped_weapon->id == weapon_rpg)
		player_shoot_projectile(app, origin);
	else if (app->player.equipped_weapon->id == weapon_shotgun)
		shoot_shotgun(app, origin);
	if (app->player.equipped_weapon != weapon_fist)
		app->player.equipped_weapon->ammo--;
}
