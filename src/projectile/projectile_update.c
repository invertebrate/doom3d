/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:53:38 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 21:39:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	deal_collision(t_doom3d *app, t_3d_object *obj, t_3d_object *hit)
{
	t_projectile	*projectile;

	projectile = obj->params;
	if (projectile->type == projectile_type_rpg)
		projectile_explosion(app, obj->position, projectile);
	(void)hit; // unused currently
	//if (projectile->type = projectile_type_bullet)
	//	npc_trigger_on_projectile_hit(app, hit, obj);
	object_set_for_deletion(app, obj);
	ft_printf("Deleted projectile! \n"); //test
}

static void	check_collision(t_doom3d *app, t_3d_object *projectile)
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
		ml_vector3_sub(obj->position, projectile->position, dist);
		if (ml_vector3_mag(dist) < 100 * app->unit_size
				&& obj->type != object_type_projectile
				&& obj->type != object_type_trigger)
			if (l3d_aabb_collides(&obj->aabb, &projectile->aabb))
			{
				deal_collision(app, projectile, obj);
				ft_printf("PROJECTILE COLLISION with obj type |%d|!\n", obj->type);//test
			}
	}
}

void		projectile_update(t_doom3d *app, t_3d_object *obj)
{
	t_projectile	*projectile;
	t_vec3			pos_new;

	projectile = obj->params;
	ml_vector3_add(obj->position, projectile->dir, pos_new);
	ml_vector3_copy(pos_new, obj->position);
	l3d_3d_object_translate(obj, projectile->dir[0], projectile->dir[1], projectile->dir[2]);
	projectile->traveled += projectile->speed;
	check_collision(app, obj);
	if (obj && projectile->traveled > projectile->range)
	{
		object_set_for_deletion(app, obj);
		ft_printf("Deleted projectile! \n"); //test
	}
}
