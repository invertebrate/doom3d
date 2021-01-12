/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:50:53 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 21:29:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	weapons_init(t_doom3d *app)
{
	int	i;

	weapons_init_data(app);
	i = -1;
	while (++i < NUM_WEAPONS)
		ft_memcpy(&app->player.weapons[i],
			&app->weapons_data[i], sizeof(t_weapon));
	weapon_equip(app, weapon_shotgun);
}
