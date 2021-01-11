/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:51:46 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 14:03:11 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_shoot_ray(t_doom3d *app, t_vec3 origin)
{
	t_hits	*hits;
	t_hit	*closest_triangle_hit;
	t_vec3	dist;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		app->player.forward, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit);
		if (closest_triangle_hit != NULL)
		{
			ml_vector3_sub(closest_triangle_hit->hit_point, origin, dist);
			ft_printf("Hit at object type %d, at distance: %f, ", closest_triangle_hit->triangle->parent->type, ml_vector3_mag(dist));
			ml_vector3_print(closest_triangle_hit->hit_point);
			if (ml_vector3_mag(dist) <= app->player.equipped_item->range)
				if (closest_triangle_hit->triangle->parent->type == object_type_npc)
					npc_trigger_onhit(app, closest_triangle_hit->triangle->parent);
		}
		l3d_delete_hits(&hits);
	}
}

static void		place_projectile_object_in_scene(t_doom3d *app,
										t_projectile *projectile, t_vec3 pos)
{
	t_3d_object *obj;

	place_scene_object(app,
		(const char*[3]){projectile->model_key, projectile->texture_key,
								projectile->normal_map_key}, pos);
	obj = app->active_scene->objects[app->active_scene->num_objects - 1];
	obj->type = object_type_projectile;
	ml_vector3_normalize(app->player.forward, projectile->dir);
	l3d_3d_object_set_params(obj, projectile, sizeof(t_projectile),
								projectile->type);
	//l3d_3d_object_rotate(obj, 0, ANGLE, 0);
	//l3d_3d_object_scale(obj, 0.2, 0.2, 0.2);
}

void	player_shoot_projectile(t_doom3d *app, t_vec3 origin)
{
	t_projectile	projectile;

	ft_memset(&projectile, 0, sizeof(t_projectile));
	projectile = app->projectile_data[app->player.equipped_item->item];
	//projectile.angle = angle;
	place_projectile_object_in_scene(app, &projectile, origin);
}
