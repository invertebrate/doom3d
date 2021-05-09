/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:16:45 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/08 14:05:03 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	place_projectile_object_in_scene(t_doom3d *app,
					t_projectile *projectile, t_vec3 origin, t_vec3 rot)
{
	t_3d_object	*obj;

	obj = place_scene_object(app,
			(const char *[3]){projectile->model_key, projectile->texture_key,
			projectile->normal_map_key}, origin);
	obj->type = object_type_projectile;
	l3d_3d_object_set_params(obj, projectile, sizeof(t_projectile),
		projectile->type);
	l3d_3d_object_rotate(obj, rot[0], rot[1], rot[2]);
	l3d_3d_object_scale(obj, 0.1, 0.1, 0.1);
	l3d_object_aabb_update(obj);
	if (app->is_debug)
		LOG_DEBUG("Spawned projectile id: %d", obj->id);
}

void	projectile_data_init(t_doom3d *app)
{
	app->projectile_data[projectile_type_rpg] = projectile_data_rpg(app);
	app->projectile_data[projectile_type_fireball]
		= projectile_data_fireball(app);
	app->projectile_data[projectile_type_fireball_green]
		= projectile_data_fireball_custom(app, projectile_type_fireball_green);
	app->projectile_data[projectile_type_fireball_purple]
		= projectile_data_fireball_custom(app, projectile_type_fireball_purple);
}
