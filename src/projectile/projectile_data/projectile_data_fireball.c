/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_data_fireball.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:59:58 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/08 16:28:29 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_projectile	projectile_data_fireball(t_doom3d *app)
{
	t_projectile projectile;

	projectile.type = projectile_type_fireball;
	projectile.damage = 10;
	projectile.speed = 100.0;
	projectile.range = 100 * app->unit_size;
	projectile.traveled = 0;
	projectile.radius = 5 * app->unit_size;
	projectile.model_key = "assets/models/npc_projectile.obj";
	projectile.texture_key = "assets/textures/npc_projectile_texture.bmp";
	projectile.normal_map_key = NPC_MONSTER01_NORMM;
	return (projectile);
}
