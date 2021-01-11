/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_glock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:04:24 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 12:11:34 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_item	item_data_glock(t_doom3d *app)
{
	t_item	item;

	item.item = item_glock;
	item.item_type = item_type_sidearm;
	item.ammo = 20;
	item.fire_type = fire_ray;
	item.fire_rate = 4;
	item.range = 80 * app->unit_size;
	item.damage = 20;
	return (item);
}
