/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_data_shotgun.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:20:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/02 15:09:29 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_weapon	weapon_data_shotgun(t_doom3d *app)
{
	t_weapon	item;

	item.id = weapon_shotgun;
	item.ammo = 32;
	item.clip = 8;
	item.clip_size = 8;
	item.fire_rate = 3.0;
	item.range = 80 * app->unit_size;
	item.damage_per_hit = 5;
	item.projectile = projectile_type_bullet;
	return (item);
}
