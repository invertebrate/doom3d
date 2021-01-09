/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_equip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:33:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/09 14:51:12 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
	if weapon slot is empty (-1), prevents equipping the slot
*/

void	inventory_equip(t_doom3d *app, int slot)
{
	if (app->player.item[slot].ammo > -1)
	{
		app->player.equipped_item = &(app->player.item[slot]);
	}
	if (app->player.equipped_item->item == item_fist) //test
		ft_printf("equipped item is now |item_fist|\n"); //test
	if (app->player.equipped_item->item == item_glock) //test
		ft_printf("equipped item is now |item_glock|\n"); //test
	if (app->player.equipped_item->item == item_rpg) //test
		ft_printf("equipped item is now |item_rpg|\n"); //test
}