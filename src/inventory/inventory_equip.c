/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_equip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 22:33:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/25 12:40:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	weapon_equip(t_doom3d *app, t_weapon_id slot)
{
	app->player.equipped_weapon = &app->player.weapons[slot];
	if (app->player.equipped_weapon->id == weapon_fist)
	{
		if (app->settings.is_debug)
			LOG_DEBUG("Equipped item |weapon_fist|");
	}
	if (app->player.equipped_weapon->id == weapon_pistol)
	{
		if (app->settings.is_debug)
			LOG_DEBUG("Equipped item |weapon_pistol|");
	}
	if (app->player.equipped_weapon->id == weapon_rpg)
	{
		if (app->settings.is_debug)
			LOG_DEBUG("Equipped item |weapon_rpg|");
	}
	if (app->player.equipped_weapon->id == weapon_shotgun)
	{
		if (app->settings.is_debug)
			LOG_DEBUG("Equipped item |weapon_shotgun|");
	}
}
