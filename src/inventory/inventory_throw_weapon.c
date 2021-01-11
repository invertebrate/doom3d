/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_throw_weapon.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:14:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/10 13:04:05 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	inventory_throw_weapon(t_doom3d *app)
{
	if (app->player.equipped_item->item != item_fist)
		app->player.equipped_item->ammo = -1;
	if (app->player.equipped_item->item == item_type_melee)
		app->player.item[0] = (t_item) {item_fist, item_type_melee, 0,
										fire_ray, 2, 5 * app->unit_size, 5};
	app->player.equipped_item = &(app->player.item[item_fist]);
	ft_printf("Threw away item!\n");//test
}