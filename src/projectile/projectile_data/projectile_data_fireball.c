/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_data_fireball.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:59:58 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/07 16:15:47 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_projectile	projectile_data_fireball_custom(t_doom3d *app, int type)
{
	t_projectile	projectile;

	projectile = projectile_data_fireball(app);
	projectile.type = type;
	if (type == projectile_type_fireball_green)
	{
		projectile.texture_key = NPC_PROJECTILE_01;
		projectile.damage *= 1.5f;
		projectile.range *= 0.8f;
	}
	else if (type == projectile_type_fireball_purple)
	{
		projectile.texture_key = NPC_PROJECTILE_02;
		projectile.radius *= 5;
		projectile.damage *= 2;
		projectile.speed *= 0.7;
	}
	return (projectile);
}

t_projectile	projectile_data_fireball(t_doom3d *app)
{
	t_projectile	projectile;

	projectile.type = projectile_type_fireball;
	projectile.damage = 50;
	projectile.speed = 250.0;
	projectile.range = 100 * app->unit_size;
	projectile.traveled = 0;
	projectile.radius = 5 * app->unit_size;
	projectile.model_key = "assets/models/npc_projectile.obj";
	projectile.texture_key = NPC_PROJECTILE_00;
	projectile.normal_map_key = MONSTER01_NORMM;
	return (projectile);
}
