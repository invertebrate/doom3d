/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_pickup_weapon.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:26:50 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/09 00:14:38 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	inventory_pickup_weapon(t_doom3d *app, t_item item)
{
	if (item.item_type == item_type_melee)
		if (app->player.item[item_type_melee].item == item_fist)
			app->player.item[item_type_melee] = item;
	if (item.item_type == item_type_sidearm)
		if (app->player.item[item_type_sidearm].ammo == -1)
			app->player.item[item_type_sidearm] = item;
	if (item.item_type == item_type_weapon)
		if (app->player.item[item_type_weapon].ammo == -1)
			app->player.item[item_type_weapon] = item;
}