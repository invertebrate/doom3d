/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:51:46 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/09 19:54:29 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_shoot_ray(t_doom3d *app, t_vec3 origin)
{
	t_hits	*hits;
	t_hit	*closest_triangle_hit;
	t_vec3	dist_vec3;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		app->player.forward, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit);
		if (closest_triangle_hit != NULL)
		{
			ml_vector3_sub(closest_triangle_hit->hit_point, origin, dist_vec3);
			if (ml_vector3_mag(dist_vec3) <= app->player.equipped_item->range)
			{
				ft_printf("Hit at: ");
				ml_vector3_print(closest_triangle_hit->hit_point);
				//todo:
				//if (closest_triangle_hit->triangle->parent->type == object_type_npc)
					//npc_trigger_onhit(closest_triangle_hit->triangle->parent->id, app->player.equipped_item->item);
			}
		}
		l3d_delete_hits(&hits);
	}
}
