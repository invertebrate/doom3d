/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_explosion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:45:28 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 22:32:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	projectile_explosion(t_doom3d *app, t_vec3 pos, t_projectile *projectile)
{
	t_vec3		dist;
	float		mag;
	int			damage;
	int			i;
	t_3d_object	*obj;

	ft_printf("PROJECTILE EXPLOSION!\n");//test
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
							app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		ml_vector3_sub(obj->position, pos, dist);
		if ((mag = ml_vector3_mag(dist)) < projectile->radius
				&& obj->type == object_type_npc)
		{
			//damage = projectile->damage;
			damage = projectile->damage / (1 + (mag / (app->unit_size * 10))) + 0.5 * projectile->damage;
			npc_trigger_onhit_explosion(app, obj, damage);
		}
	}
}