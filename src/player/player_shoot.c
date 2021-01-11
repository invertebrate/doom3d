/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:51:46 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 22:44:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_shoot_ray(t_doom3d *app, t_vec3 origin, t_vec3 dir)
{
	t_hits	*hits;
	t_hit	*closest_triangle_hit;
	t_vec3	dist;
	char	object_type[128];

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		dir, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit);
		if (closest_triangle_hit != NULL)
		{
			ml_vector3_sub(closest_triangle_hit->hit_point, origin, dist);
			object_type_to_str(closest_triangle_hit->triangle->parent,
				object_type);
			ft_printf("Hit %s, at unit distance: %f, ", object_type,
				ml_vector3_mag(dist) / app->unit_size);
			ml_vector3_print(closest_triangle_hit->hit_point);
			if (ml_vector3_mag(dist) <= app->player.equipped_weapon->range)
				if (closest_triangle_hit->triangle->parent->type == object_type_npc)
					npc_trigger_onhit(app, closest_triangle_hit->triangle->parent);
		}
		l3d_delete_hits(&hits);
	}
}
