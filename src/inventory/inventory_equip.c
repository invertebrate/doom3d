/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_equip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:33:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/05 18:15:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	weapon_equip(t_doom3d *app, t_weapon_id slot)
{
	app->player.equipped_weapon = &app->player.weapons[slot];
	if (app->player.equipped_weapon->id == weapon_fist)
	{
		if (app->is_debug)
			LOG_INFO("Equipped item |weapon_fist|");
	}
	if (app->player.equipped_weapon->id == weapon_glock)
	{
		if (app->is_debug)
			LOG_INFO("Equipped item |weapon_glock|");
	}
	if (app->player.equipped_weapon->id == weapon_rpg)
	{
		if (app->is_debug)
			LOG_INFO("Equipped item |weapon_rpg|");
	}
	if (app->player.equipped_weapon->id == weapon_shotgun)
	{
		if (app->is_debug)
			LOG_INFO("Equipped item |weapon_shotgun|");
	}
}