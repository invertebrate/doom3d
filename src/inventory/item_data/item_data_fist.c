/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_fist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:54:55 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 13:54:11 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_item	item_data_fist(t_doom3d *app)
{
	t_item	item;

	item.item = item_fist;
	item.item_type = item_type_melee;
	item.ammo = 0;
	item.fire_type = fire_ray;
	item.fire_rate = 2;
	item.range = 5 * app->unit_size;
	item.damage = 5;
	item.projectile = 0;
	return (item);
}
