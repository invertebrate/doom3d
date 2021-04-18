/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_grounded.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:15:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/18 20:35:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_3d_object	*object_under(t_doom3d *app,
					t_vec3 origin, uint32_t self_id, t_vec3 hit_point)
{
	t_hits		*hits;
	t_hit		*closest_hit;
	t_3d_object	*hit_parent;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		(t_vec3){0, Y_DIR, 0}, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_hit, self_id);
		if (!closest_hit)
		{
			l3d_delete_hits(&hits);
			return (NULL);
		}
		hit_parent = closest_hit->triangle->parent;
		ml_vector3_copy(closest_hit->hit_point, hit_point);
		l3d_delete_hits(&hits);
		return (hit_parent);
	}
	return (NULL);
}

static t_3d_object	*object_above(t_doom3d *app,
					t_vec3 origin, uint32_t self_id, t_vec3 hit_point)
{
	t_hits		*hits;
	t_hit		*closest_hit;
	t_3d_object	*hit_parent;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		(t_vec3){0, -Y_DIR, 0}, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_hit, self_id);
		if (!closest_hit)
		{
			l3d_delete_hits(&hits);
			return (NULL);
		}
		hit_parent = closest_hit->triangle->parent;
		ml_vector3_copy(closest_hit->hit_point, hit_point);
		l3d_delete_hits(&hits);
		return (hit_parent);
	}
	return (NULL);
}

/*
** 1. Check objects exist under by casting rays from corners and bottom center
** of aabb.
** 2. If object under exists, check it collides with self aabb.
*/
t_bool	obj_is_grounded(t_doom3d *app, t_3d_object *falling_obj)
{
	t_3d_object	*obj_under;
	t_vec3		origin;
	t_vec3		hit_point;
	t_bool		ret;

	ret = false;
	ml_vector3_copy((t_vec3){falling_obj->aabb.center[0],
				falling_obj->aabb.center[1] + falling_obj->aabb.size[1] / 2.0,
				falling_obj->aabb.center[2]}, origin);
	obj_under = object_under(app, origin, falling_obj->id, hit_point);
	if (obj_under)
	{
		if (hit_point[1] <= origin[1] &&
			hit_point[1] >= origin[1] - falling_obj->aabb.size[1] * 1.5 &&
						obj_under->type != object_type_projectile &&
						obj_under->type != object_type_npc)
			ret = true;
	}
	return (ret);
}

/*
** 1. Check objects exist under by casting rays from corners and bottom center
** of aabb.
** 2. If object under exists, check it collides with self aabb.
*/
t_bool	player_is_grounded(t_doom3d *app)
{
	t_3d_object	*obj_under;
	t_vec3		origin;
	t_vec3		hit_point;
	t_bool		ret;

	ret = false;
	ml_vector3_copy((t_vec3){app->player.aabb.center[0],
				app->player.aabb.center[1] + app->player.aabb.size[1] / 2.0,
				app->player.aabb.center[2]}, origin);
	obj_under = object_under(app, origin, -1, hit_point);
	if (obj_under)
	{
		if (hit_point[1] <= origin[1] &&
			hit_point[1] >= origin[1] - app->player.aabb.size[1] &&
						obj_under->type != object_type_projectile &&
						obj_under->type != object_type_npc)
			ret = true;
	}
	return (ret);
}

void			nudge_player_down_ceiling(t_doom3d *app)
{
	int	i;

	i = -1;
	while (player_hits_ceiling(app) && ++i < app->player.aabb.size[1] / 20)
	{
		app->player.pos[1] += 10;
		player_update_aabb(&app->player);
	}
}

t_bool			player_hits_ceiling(t_doom3d *app)
{
	t_3d_object	*obj_above;
	t_vec3		origin;
	t_vec3		hit_point;
	t_bool		ret;

	ret = false;
	ml_vector3_copy((t_vec3){app->player.aabb.center[0],
				app->player.aabb.center[1] - app->player.aabb.size[1] / 2.0,
				app->player.aabb.center[2]}, origin);
	obj_above = object_above(app, origin, -1, hit_point);
	if (obj_above)
	{
		if (hit_point[1] >= origin[1] &&
			hit_point[1] <= origin[1] + app->player.aabb.size[1] / 2 &&
						obj_above->type != object_type_projectile &&
						obj_above->type != object_type_npc)
			ret = true;
	}
	return (ret);
}

static void		nudge_player_down(t_doom3d *app)
{
	int	i;

	i = -1;
	while (!player_is_grounded(app) && ++i < app->player.aabb.size[1] / 20)
	{
		app->player.pos[1] += 10;
		player_update_aabb(&app->player);
	}
	if (player_is_grounded(app))
	{
		app->player.pos[1] -= 10;
		player_update_aabb(&app->player);
	}
}

static t_3d_object	*object_under_nudge(t_doom3d *app,
					t_vec3 origin, uint32_t self_id, t_vec3 hit_point)
{
	t_hits		*hits;
	t_hit		*closest_hit;
	t_3d_object	*hit_parent;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		(t_vec3){0, -Y_DIR, 0}, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_hit, self_id);
		if (!closest_hit)
		{
			l3d_delete_hits(&hits);
			return (NULL);
		}
		hit_parent = closest_hit->triangle->parent;
		ml_vector3_copy(closest_hit->hit_point, hit_point);
		l3d_delete_hits(&hits);
		return (hit_parent);
	}
	return (NULL);
}

t_bool	player_check_nudge_to_ground(t_doom3d *app)
{
	t_3d_object	*obj_under;
	t_vec3		origin;
	t_vec3		hit_point;
	t_bool		ret;
	t_vec3		tmp;

	ret = false;
	ml_vector3_copy((t_vec3){app->player.aabb.center[0],
				app->player.aabb.center[1] + app->player.aabb.size[1] / 2.0,
				app->player.aabb.center[2]}, origin);
	obj_under = object_under_nudge(app, origin, -1, hit_point);
	if (obj_under)
	{
		ml_vector3_sub(hit_point, origin, tmp);
		if (ml_vector3_mag(tmp) < app->player.aabb.size[1] / 2 &&
						obj_under->type != object_type_projectile &&
						obj_under->type != object_type_npc)
		{
			nudge_player_down(app);
			ret = true;
		}
	}
	return (ret);
}