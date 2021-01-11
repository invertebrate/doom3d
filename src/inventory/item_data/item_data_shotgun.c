/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_shotgun.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:20:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/11 23:14:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_shotgun(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_shotgun;
	item.ammo = 10;
	item.fire_rate = 3.0;
	item.range = 80 * app->unit_size;
	item.damage_per_hit = 5;
	return (item);
}
