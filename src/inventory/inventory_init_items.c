/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_init_items.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:15:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 12:16:13 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	inventory_init_items(t_doom3d *app)
{
	app->item_data[item_fist] = item_data_fist(app);
	app->item_data[item_glock] = item_data_glock(app);
	app->item_data[item_rpg] = item_data_rpg(app);
}