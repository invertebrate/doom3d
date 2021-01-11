/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_fist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:54:55 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 19:03:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_fist(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_fist;
	item.item_type = item_type_weapon;
	item.ammo = 0;
	item.fire_type = fire_ray;
	item.fire_rate = 2;
	item.range = 5 * app->unit_size;
	item.damage = 5;
	return (item);
}
