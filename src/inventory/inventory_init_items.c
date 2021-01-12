/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_init_items.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:15:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 19:04:22 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	weapons_init_data(t_doom3d *app)
{
	app->weapons_data[weapon_fist] = weapon_data_fist(app);
	app->weapons_data[weapon_glock] = weapon_data_glock(app);
	app->weapons_data[weapon_shotgun] = weapon_data_shotgun(app);
	app->weapons_data[weapon_rpg] = weapon_data_rpg(app);
}