/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_pistol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:12:35 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/11 18:35:41 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_pistol(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_pistol;
	item.ammo = 120;
	item.clip = 20;
	item.clip_size = 20;
	item.fire_rate = 4.0;
	item.range = 80 * app->unit_size;
	item.projectile = projectile_type_bullet;
	item.damage_per_hit = 20;
	return (item);
}
