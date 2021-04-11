/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/11 19:59:14 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** https://gamedev.stackexchange.com/questions/49956/
** collision-detection-smooth-wall-sliding-no-bounce-effect
*/

static void		limit_movement_add_by_collision(t_doom3d *app,
							t_hit *hit, t_vec3 dir, t_player *future_player)
{
	if (dir[0] > 0)
	{
		if (future_player->aabb.xyz_max[0] > hit->hit_point[0])
			app->player.pos[0] -= future_player->aabb.xyz_max[0] - hit->hit_point[0];
	}
	else
	{
		if (future_player->aabb.xyz_min[0] < hit->hit_point[0])
			app->player.pos[0] += future_player->aabb.xyz_min[0] - hit->hit_point[0];
	}
	if (dir[2] > 0)
	{
		if (future_player->aabb.xyz_max[2] > hit->hit_point[2])
			app->player.pos[2] -= future_player->aabb.xyz_max[2] - hit->hit_point[2];
	}
	else
	{
		if (future_player->aabb.xyz_min[2] < hit->hit_point[2])
			app->player.pos[2] += future_player->aabb.xyz_min[2] - hit->hit_point[2];
	}
	player_update_aabb(&app->player);
}

static void		set_future_player(t_doom3d *app, t_vec3 add,
					t_player *future_player)
{
	ft_memcpy(future_player, &app->player, sizeof(t_player));
	ml_vector3_add(future_player->pos, add, future_player->pos);
	player_update_aabb(future_player);
}
/*
static t_hit	*l3d_get_aabb_hit_record_point(t_vec3 origin, t_box3d *target)
{
	t_vec3		dir;
	t_ray		ray;
	t_hits		*hits;
	t_hit		*hit;

	ml_vector3_sub(target->center, origin, dir);
	l3d_ray_set(dir, origin, &ray);
	hits = NULL;
	if (l3d_bounding_box_ray_hit(target, &ray, &hits, true))
	{
		error_check(!(hit = ft_calloc(sizeof(t_hit))), "Failed to malloc hit");
		ft_memcpy(hit, ((t_hit*)hits->content), sizeof(t_hit));
		l3d_delete_hits(&hits);
		return (hit);
	}
	return (NULL);
}*/

void			collision_limit_player(t_doom3d *app, t_vec3 add)
{
	t_player	future_player;
	t_hit		*closest_hit;
	t_hits		*hits;
	t_vec3		dir;

	if (ml_vector3_mag(add) == 0)
		return ;
	set_future_player(app, add, &future_player);
	ml_vector3_normalize(add, dir);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.aabb.center,
		dir, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_hit, -1);
		if (closest_hit)
			limit_movement_add_by_collision(app, closest_hit, dir, &future_player);
		l3d_delete_hits(&hits);
	}
}
