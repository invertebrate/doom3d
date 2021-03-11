/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_line_of_sight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:24:25 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/04 17:20:42 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	npc_ray_to_npc(t_doom3d *app, t_vec3 origin, t_vec3 dir, 
														t_3d_object *npc_obj)
{
	t_hits	*hits;
	t_hit	*closest_triangle_hit;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		dir, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit, -1);
		if (closest_triangle_hit != NULL)
		{
			if (closest_triangle_hit->triangle->parent == npc_obj)
				return (true);
		}
		l3d_delete_hits(&hits);
	}
	ft_printf("something blocking line of sight! \n");//test
	return (false);
}

t_bool			npc_has_line_of_sight(t_doom3d *app, t_3d_object *npc_obj)
{
	t_vec3	diff;
	t_vec3	dir;

	dir[0] = 0.0;
	dir[1] = 0.0;
	dir[2] = 0.0;
	ml_vector3_sub(npc_obj->aabb.center, app->player.aabb.center, diff);
	ml_vector3_normalize(diff, dir);
	return (npc_ray_to_npc(app, app->player.pos, dir, npc_obj));
}