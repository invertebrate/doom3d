/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_rpg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:08:25 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 21:39:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_rpg(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_rpg;
	item.ammo = 10;
	item.fire_rate = 0.25;
	item.range = 100 * app->unit_size;
	item.projectile = projectile_type_rpg;
	item.damage_per_hit = 100;
	return (item);
}
