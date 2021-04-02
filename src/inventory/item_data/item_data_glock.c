/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_glock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:04:24 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/02 15:09:17 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_glock(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_glock;
	item.ammo = 120;
	item.clip = 20;
	item.clip_size = 20;
	item.fire_rate = 4.0;
	item.range = 80 * app->unit_size;
	item.projectile = projectile_type_bullet;
	item.damage_per_hit = 20;
	return (item);
}
