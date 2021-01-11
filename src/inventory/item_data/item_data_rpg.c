/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_rpg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:08:25 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 12:11:14 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_item	item_data_rpg(t_doom3d *app)
{
	t_item	item;

	item.item = item_rpg;
	item.item_type = item_type_weapon;
	item.ammo = 10;
	item.fire_type = fire_projectile;
	item.fire_rate = 0.25;
	item.range = 100 * app->unit_size;
	item.damage = 100;
	return (item);
}
