/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_glock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:04:24 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 15:49:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_glock(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_glock;
	item.ammo = 20;
	item.fire_rate = 4.0;
	item.range = 80 * app->unit_size;
	item.damage_per_hit = 20;
	return (item);
}
