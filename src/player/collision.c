/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/30 22:29:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Updates the sphere collider and casts rays.
*/

void	player_colliders_update(t_doom3d *app)
{
	ml_vector3_copy(app->player.pos, app->player.collider.sphere.pos);
	if (app->player.is_crouching)
		app->player.collider.sphere.radius = ((PLAYER_HEIGHT / 2) - 0.01)
			* app->unit_size / 2;
	else
		app->player.collider.sphere.radius = ((PLAYER_HEIGHT / 2) - 0.01)
			* app->unit_size;
	l3d_cast_rays_sphere(app->player.collider.rays,
		(uint32_t[2]){COLLIDER_RAY_COUNT, COLLIDER_RAY_COUNT},
		&app->player.collider.sphere);
	ml_vector3_copy(app->player.pos, app->player.collider_ground.cylinder.pos);
	app->player.collider_ground.cylinder.height
		= app->player.player_height / 2;
	l3d_cast_rays_cylinder(app->player.collider_ground.rays,
		(uint32_t[2]){COLLIDER_RAY_COUNT, COLLIDER_RAY_COUNT},
		&app->player.collider_ground.cylinder);
	return ;
}

t_bool	is_player_grounded(t_doom3d *app)
{
	t_hits			*hits;
	t_ray			ray;
	int32_t			i;
	t_hit			*tri_hit;

	i = -1;
	hits = NULL;
	while (++i < COLLIDER_RAY_TOTAL)
	{
		ray = app->player.collider_ground.rays[i];
		if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree,
				ray.origin, ray.dir, &hits))
		{
			tri_hit = NULL;
			l3d_get_closest_triangle_hit_at_range(hits, &tri_hit,
				-1, app->player.collider_ground.cylinder.height);
			if (tri_hit != NULL && ml_vector3_dot(ray.dir, tri_hit->normal) < 0)
			{
				l3d_delete_hits(&hits);
				return (true);
			}
			l3d_delete_hits(&hits);
		}
	}
	return (false);
}
