/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_throw_weapon.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:14:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 21:28:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	inventory_throw_weapon(t_doom3d *app)
{
	if (app->player.equipped_weapon->id != weapon_fist)
		app->player.equipped_weapon->ammo = 0;
	app->player.equipped_weapon = &(app->player.weapons[weapon_fist]);
	ft_printf("Threw away item!\n");//test
}