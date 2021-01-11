/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_pickup_weapon.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:26:50 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 19:00:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	inventory_pickup_weapon(t_doom3d *app, t_weapon item)
{
	if (item.id == weapon_rpg || item.id == weapon_fist ||
		item.id == weapon_shotgun || item.id == weapon_glock)
		app->player.weapons[item.id].ammo += item.ammo;
	ft_printf("Weapon: %d, Ammo: %d\n", item.id,
		app->player.weapons[item.id].ammo);
}