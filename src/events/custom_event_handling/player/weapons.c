/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 00:08:47 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 18:37:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_player_shoot_projectile(t_doom3d *app)
{
	t_vec3			origin;
	t_vec3			add;

	if (app->player.equipped_weapon->id != weapon_fist)
		check_npc_hearing(app, app->player.aabb.center);
	ml_vector3_mul(app->player.forward, NEAR_CLIP_DIST, add);
	ml_vector3_add(app->player.pos, add, origin);
	player_shoot_projectile(app, origin);
}

void	handle_player_reload(t_doom3d *app)
{
	player_reload(app);
}

void	handle_player_weapon_equip(t_doom3d *app, t_weapon_id weapon)
{
	if (player_animation_state(app) != anim_state_default)
		return ;
	weapon_equip(app, weapon);
}
