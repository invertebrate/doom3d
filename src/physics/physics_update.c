/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:49:15 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/14 18:11:21 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	physics_update_gravity(t_doom3d *app, t_3d_object *target)
{
	t_npc	*npc;

	npc = target->params;
	if (physics_is_grounded(app, target))
		npc->y_velocity = 0;
	else
	{
		npc->y_velocity += app->info.delta_time / 10;
		l3d_3d_object_translate(target, 0, npc->y_velocity, 0);
	}
}
