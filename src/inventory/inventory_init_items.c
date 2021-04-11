/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_init_items.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:15:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/07 14:19:42 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	weapons_init_data(t_doom3d *app)
{
	app->weapons_data[weapon_fist] = weapon_data_fist(app);
	app->weapons_data[weapon_pistol] = weapon_data_pistol(app);
	app->weapons_data[weapon_shotgun] = weapon_data_shotgun(app);
	app->weapons_data[weapon_rpg] = weapon_data_rpg(app);
}
