/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:22:43 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/29 17:58:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_interact(t_doom3d *app)
{
	int			i;
	t_3d_object	*obj;
	t_vec3		dist;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		if (obj->type != object_type_trigger)
			continue ;
		ml_vector3_sub(obj->position, app->player.pos, dist);
		if (ml_vector3_mag(dist) < app->unit_size * 3)
			trigger_activate(app, obj);
	}
}
