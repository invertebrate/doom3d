/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:50:53 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 14:05:12 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	inventory_init(t_doom3d *app)
{
	int	i;

	inventory_init_items(app);
	app->player.item[0] = app->item_data[item_fist];
	app->player.item[1] = app->item_data[item_glock];
	i = 2;
	while (i < INVENTORY_SIZE)
	{
		app->player.item[i] = (t_item) {0, 0, -1, 0, 0, 0, 0, 0};
		i++;
	}
	app->player.equipped_item = &(app->player.item[item_type_melee]);
}
