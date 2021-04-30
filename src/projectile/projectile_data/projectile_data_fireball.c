/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_data_fireball.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 13:59:58 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/30 16:53:22 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_projectile	projectile_data_fireball_custom(t_doom3d *app, int type)
{
	t_projectile	projectile;

	projectile = projectile_data_fireball(app);
	projectile.type = type;
	// if (type == projectile_type_fireball_blue) // tiny range, huge dmg
	// {
	// 	projectile.texture_key = NPC_PROJECTILE_01;
	// 	projectile.damage *= 5;
	// 	projectile.range *= 0.1f;
	// 	projectile.radius *= 0.8f;
	// }
	if (type == projectile_type_fireball_green) // smaller range, higher dmg
	{
		projectile.texture_key = NPC_PROJECTILE_02;
		projectile.damage *= 1.5f;
		projectile.range *= 0.8f;
	}
	else if (type == projectile_type_fireball_lgreen) // small range, high dmg
	{
		projectile.texture_key = NPC_PROJECTILE_03;
		projectile.damage *= 2;
		projectile.range *= 0.5f;
	}
	else if (type == projectile_type_fireball_pink) // super fast, low dmg
	{
		projectile.texture_key = NPC_PROJECTILE_04;
		projectile.damage *= 0.1f;
		projectile.speed *= 5;
		projectile.radius *= 0.01f;
	}
	else if (type == projectile_type_fireball_yellow) // faster, lower dmg
	{
		projectile.texture_key = NPC_PROJECTILE_05;
		projectile.damage *= 0.5f;
		projectile.speed *= 3;
	}
	else if (type == projectile_type_fireball_purple) // big explosion, slow
	{
		projectile.texture_key = NPC_PROJECTILE_06;
		projectile.radius *= 5;
		projectile.speed *= 0.8f;
		projectile.speed *= 0.7;
	}
	return (projectile);
}

t_projectile	projectile_data_fireball(t_doom3d *app)
{
	t_projectile	projectile;

	projectile.type = projectile_type_fireball;
	projectile.damage = 10;
	projectile.speed = 350.0;
	projectile.range = 100 * app->unit_size;
	projectile.traveled = 0;
	projectile.radius = 5 * app->unit_size;
	projectile.model_key = "assets/models/npc_projectile.obj";
	projectile.texture_key = NPC_PROJECTILE_00;
	projectile.normal_map_key = NPC_MONSTER01_NORMM;
	return (projectile);
}
