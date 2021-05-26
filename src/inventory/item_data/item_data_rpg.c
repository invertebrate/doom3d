/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_rpg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:08:25 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/26 16:44:28 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_rpg(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_rpg;
	item.ammo = 10;
	item.clip = 1;
	if (app->settings.is_hard)
	{
		item.ammo = 0;
		item.clip = 0;
	}
	item.clip_size = 1;
	item.fire_rate = 1;
	item.range = 100 * app->unit_size;
	item.projectile = projectile_type_rpg;
	item.damage_per_hit = 500;
	return (item);
}
