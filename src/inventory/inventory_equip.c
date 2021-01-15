/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_equip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:33:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 21:54:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	weapon_equip(t_doom3d *app, t_weapon_id slot)
{
	app->player.equipped_weapon = &app->player.weapons[slot];
	if (app->player.equipped_weapon->id == weapon_fist) //test
	{
		ft_printf("equipped item is now |weapon_fist|\n"); //test
	}
	if (app->player.equipped_weapon->id == weapon_glock) //test
	{
		ft_printf("equipped item is now |weapon_glock|\n"); //test
	}
	if (app->player.equipped_weapon->id == weapon_rpg) //test
	{
		ft_printf("equipped item is now |weapon_rpg|\n"); //test
	}
	if (app->player.equipped_weapon->id == weapon_shotgun) //test
	{
		ft_printf("equipped item is now |weapon_shotgun|\n"); //test
	}
}