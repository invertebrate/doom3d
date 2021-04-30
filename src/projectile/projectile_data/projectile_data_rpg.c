/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_data_rpg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:17:24 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/08 15:53:44 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_projectile	projectile_data_rpg(t_doom3d *app)
{
	t_projectile projectile;

	projectile.type = projectile_type_rpg;
	projectile.damage = 100;
	projectile.speed = 350.0;
	projectile.range = 100 * app->unit_size;
	projectile.traveled = 0;
	projectile.radius = 10 * app->unit_size;
	projectile.model_key = "assets/models/missile.obj";
	projectile.texture_key = MONSTER01_TEXTURE;
	projectile.normal_map_key = MONSTER01_NORMM;
	return (projectile);
}
