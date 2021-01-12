/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_data_rpg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:17:24 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 17:01:22 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_projectile	projectile_data_rpg(t_doom3d *app)
{
	t_projectile projectile;

	projectile.type = projectile_rpg;
	projectile.damage = 100;
	projectile.speed = app->unit_size / 2;
	projectile.range = 100 * app->unit_size;
	projectile.traveled = 0;
	projectile.radius = 50 * app->unit_size;
	projectile.model_key = "assets/models/missile.obj";
	projectile.texture_key = NPC_DEFAULT_TEXTURE;
	projectile.normal_map_key = NPC_DEFAULT_NORMM;
	return (projectile);
}
