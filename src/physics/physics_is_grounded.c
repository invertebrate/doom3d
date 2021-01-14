/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_is_grounded.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:15:29 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/14 18:12:39 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_bool	physics_is_grounded(t_doom3d *app, t_3d_object *falling_obj)
{
	t_vec3		dist;
	int			i;
	t_3d_object	*obj;

	i = 0;
	while (++i < (int32_t)(app->active_scene->num_objects +
							app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		ml_vector3_sub(obj->position, falling_obj->position, dist);
		if (ml_vector3_mag(dist) < 100 * app->unit_size
				&& obj->type != object_type_trigger
				&& obj->id != falling_obj->id)
			if (l3d_aabb_collides(&obj->aabb, &falling_obj->aabb))
			{
				ft_printf("object: |%d|GRAVITY COLLISION with obj type |%d|!\n", falling_obj->id, obj->type);//test
				return(true);
			}
	}
	return (false);
}