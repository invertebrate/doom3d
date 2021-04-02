/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_fist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:54:55 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/02 16:06:21 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_fist(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_fist;
	item.ammo = 1;
	item.clip = 1;
	item.clip_size = 0;
	item.fire_rate = 2;
	item.range = 5 * app->unit_size;
	item.projectile = projectile_type_none;
	item.damage_per_hit = 5;
	return (item);
}
