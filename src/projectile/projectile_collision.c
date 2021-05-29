/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 22:10:06 by phakakos          #+#    #+#             */
/*   Updated: 2021/05/29 17:58:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

int	check_projectile_collision_with_player(t_doom3d *app,
											t_3d_object *projectile_obj)
{
	if (l3d_aabb_collides(&app->player.aabb, &projectile_obj->aabb))
	{
		projectile_explode_effect(app, projectile_obj);
		push_custom_event(app, event_object_delete,
			projectile_obj, NULL);
		projectile_on_hit(app, projectile_obj, NULL);
		return (1);
	}
	return (0);
}

static t_bool	terrain_collision(t_doom3d *app,
				t_3d_object *projectile_obj, t_hit *closest_triangle_hit)
{
	projectile_explode_effect(app, projectile_obj);
	push_custom_event(app, event_object_delete,
		projectile_obj, NULL);
	projectile_on_hit(app, projectile_obj,
		closest_triangle_hit->triangle->parent);
	return (true);
}

int	projectile_check_terrain_collision(t_doom3d *app,
											t_3d_object *projectile_obj)
{
	t_hits			*hits;
	t_hit			*closest_triangle_hit;
	t_vec3			dist;
	t_projectile	*projectile;
	t_bool			ret;

	hits = NULL;
	ret = false;
	projectile = projectile_obj->params;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree,
			projectile_obj->aabb.center, projectile->dir, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_triangle_hit,
			projectile_obj->id);
		if (closest_triangle_hit != NULL)
		{
			ml_vector3_sub(closest_triangle_hit->hit_point,
				projectile_obj->aabb.center, dist);
			if (ml_vector3_mag(dist) <= app->unit_size)
				ret = terrain_collision(app, projectile_obj,
						closest_triangle_hit);
		}
		l3d_delete_hits(&hits);
	}
	return (ret);
}

static int	projectile_hit(t_doom3d *app, t_3d_object *projectile_obj,
					t_3d_object *obj)
{
	t_vec3		dist;

	if (obj && (obj->type == object_type_npc
			&& ((t_npc*)obj->params)->state == state_death_anim))
		return (false);
	ml_vector3_sub(obj->position, projectile_obj->position, dist);
	return (ml_vector3_mag(dist) < app->unit_size * 20 && obj->type
		== object_type_npc && l3d_aabb_collides(&obj->aabb,
			&projectile_obj->aabb));
}

void	projectile_handle_collision(t_doom3d *app, t_3d_object *projectile_obj)
{
	int			i;
	t_3d_object	*obj;

	i = -1;
	if (check_projectile_collision_with_player(app, projectile_obj)
		|| projectile_check_terrain_collision(app, projectile_obj))
		return ;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (!obj || obj->type == object_type_projectile
			|| obj->type == object_type_trigger || object_is_ignored(app, obj))
			continue ;
		if (projectile_hit(app, projectile_obj, obj))
		{
			projectile_explode_effect(app, projectile_obj);
			push_custom_event(app, event_object_delete,
				projectile_obj, NULL);
			projectile_on_hit(app, projectile_obj, obj);
			return ;
		}
	}
}
