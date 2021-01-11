/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_glock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:04:24 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 19:04:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_glock(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_glock;
	item.item_type = item_type_weapon;
	item.ammo = 20;
	item.fire_type = fire_ray;
	item.fire_rate = 6.66;
	item.range = 80 * app->unit_size;
	item.damage = 20;
	return (item);
}
