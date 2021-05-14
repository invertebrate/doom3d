/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:16:45 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/14 16:20:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	place_npc_projectile_in_scene(t_doom3d *app,
					t_projectile *projectile, t_vec3 origin)
{
	t_3d_object	*obj;

	obj = place_scene_object(app,
			(const char *[3]){projectile->model_key, projectile->texture_key,
			projectile->normal_map_key}, origin);
	obj->type = object_type_projectile;
	l3d_3d_object_set_params(obj, projectile, sizeof(t_projectile),
		projectile->type);
	l3d_3d_object_scale(obj, 0.1, 0.1, 0.1);
	l3d_object_aabb_update(obj);
	if (app->is_debug)
		LOG_DEBUG("Spawned projectile id: %d", obj->id);
}

void	place_missile_in_scene(t_doom3d *app,
					t_projectile *projectile, t_vec3 origin)
{
	t_3d_object	*obj;
	t_mat4		rot_x;
	t_mat4		rot_y;
	t_mat4		rot;

	obj = place_scene_object(app,
			(const char *[3]){projectile->model_key, projectile->texture_key,
			projectile->normal_map_key}, origin);
	obj->type = object_type_projectile;
	l3d_3d_object_set_params(obj, projectile, sizeof(t_projectile),
		projectile->type);
	l3d_3d_object_scale(obj, 0.1, 0.1, 0.1);
	ml_matrix4_rotation_y(ml_rad(app->player.rot_x), rot_x);
	ml_matrix4_rotation_x(ml_rad(app->player.rot_y), rot_y);
	ml_matrix4_mul(rot_x, rot_y, rot);
	l3d_3d_object_rotate_matrix(obj, rot);
	ml_matrix4_general_rotation(app->player.sideways, ml_rad(-90), rot);
	l3d_3d_object_rotate_matrix(obj, rot);
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
