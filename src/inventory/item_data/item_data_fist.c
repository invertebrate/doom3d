/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_fist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:54:55 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 23:14:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_fist(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_fist;
	item.ammo = 1;
	item.fire_rate = 2;
	item.range = 5 * app->unit_size;
	item.damage_per_hit = 5;
	return (item);
}
