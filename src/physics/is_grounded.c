/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_grounded.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:15:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/16 18:31:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	hit_close_enough_object_under(t_doom3d *app,
					t_vec3 origin, uint32_t self_id)
{
	t_hits	*hits;
	t_hit	*closest_hit;
	float	epsilon;
	float	t;

	hits = NULL;
	epsilon = 0.1;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		(t_vec3){0, Y_DIR, 0}, &hits))
	{
		l3d_get_closest_hit(hits, &closest_hit, self_id);
		if (!closest_hit)
			return (false);
		t = closest_hit->t;
		l3d_delete_hits(&hits);
		return (closest_hit != NULL &&
			(t <= 0.1 * app->unit_size));
	}
	return (false);
}

static t_bool	aabb_is_grounded(t_doom3d *app, t_box3d *aabb,
					uint32_t ignore_id)
{
	t_vec3	origin;

	ml_vector3_copy(
		(t_vec3){aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_min[2]}, origin);
	ml_vector3_copy(
		(t_vec3){aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_max[2]}, origin);
	if (hit_close_enough_object_under(app, origin, ignore_id))
		return (true);
	ml_vector3_copy(
		(t_vec3){aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_max[2]}, origin);
	if (hit_close_enough_object_under(app, origin, ignore_id))
		return (true);
	ml_vector3_copy(
		(t_vec3){aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_min[2]}, origin);
	if (hit_close_enough_object_under(app, origin, ignore_id))
		return (true);
	ml_vector3_copy(
		(t_vec3){aabb->center[0], aabb->center[1] + aabb->size[1] / 2.0,
			aabb->center[2]}, origin);
	if (hit_close_enough_object_under(app, origin, ignore_id))
		return (true);
	return (false);
}

t_bool	obj_is_grounded(t_doom3d *app, t_3d_object *falling_obj)
{
	// t_vec3		dist;
	// int			i;
	// t_3d_object	*obj;

	// i = 0;
	// while (++i < (int32_t)(app->active_scene->num_objects +
	// 						app->active_scene->num_deleted))
	// {
	// 	obj = app->active_scene->objects[i];
	// 	if (!obj)
	// 		continue ;
	// 	ml_vector3_sub(obj->position, falling_obj->position, dist);
	// 	if (ml_vector3_mag(dist) < 5 * app->unit_size
	// 			&& obj->type != object_type_trigger
	// 			&& obj->id != falling_obj->id)
	// 		if (l3d_aabb_collides(&obj->aabb, &falling_obj->aabb))
	// 		{
	// 			//ft_printf("object: |%d|GRAVITY COLLISION with obj type |%d|!\n", falling_obj->id, obj->type);//test
	// 			return(true);
	// 		}
	// }
	// return (false);
	return (aabb_is_grounded(app, &falling_obj->aabb, falling_obj->id));
}

t_bool	player_is_grounded(t_doom3d *app)
{
	// t_vec3		dist;
	// int			i;
	// t_3d_object	*obj;

	// i = 0;
	// while (++i < (int32_t)(app->active_scene->num_objects +
	// 						app->active_scene->num_deleted))
	// {
	// 	obj = app->active_scene->objects[i];
	// 	if (!obj)
	// 		continue ;
	// 	ml_vector3_sub(obj->position, app->player.pos, dist);
	// 	if (ml_vector3_mag(dist) < 5 * app->unit_size
	// 			&& obj->type != object_type_trigger)
	// 		if (l3d_aabb_collides(&obj->aabb, &app->player.aabb))
	// 		{
	// 			ft_printf("player GRAVITY COLLISION with obj type |%d|!\n", obj->type);//test
	// 			return(true);
	// 		}
	// }
	// return (false);
	return (aabb_is_grounded(app, &app->player.aabb, -1));
}