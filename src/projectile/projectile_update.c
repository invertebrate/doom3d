/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:53:38 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/12 22:37:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	deal_collision(t_doom3d *app, t_3d_object *projectile_obj, t_3d_object *hit)
{
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	if (projectile->type == projectile_type_rpg)
		projectile_explosion(app, projectile_obj->position, projectile);
	(void)hit; // unused currently
	//if (projectile->type = projectile_type_bullet)
	//	npc_trigger_on_projectile_hit(app, hit, obj);
}

static void	check_collision(t_doom3d *app, t_3d_object *projectile_obj)
{
	t_vec3		dist;
	int			i;
	t_3d_object	*obj;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
							app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		ml_vector3_sub(obj->position, projectile_obj->position, dist);
		if (ml_vector3_mag(dist) < 100 * app->unit_size
				&& obj->type != object_type_projectile
				&& obj->type != object_type_trigger)
			if (l3d_aabb_collides(&obj->aabb, &projectile_obj->aabb))
			{
				deal_collision(app, projectile_obj, obj);
				ft_printf("PROJECTILE COLLISION with obj type |%d|!\n", obj->type);//test
				object_set_for_deletion(app, projectile_obj);
				ft_printf("Deleted projectile! \n"); //test
			}
	}
}

void		projectile_update(t_doom3d *app, t_3d_object *projectile_obj)
{
	t_projectile	*projectile;
	t_vec3			pos_new;

	projectile = projectile_obj->params;
	ml_vector3_add(projectile_obj->position, projectile->dir, pos_new);
	ml_vector3_copy(pos_new, projectile_obj->position);
	l3d_3d_object_translate(projectile_obj, projectile->dir[0], projectile->dir[1], projectile->dir[2]);
	projectile->traveled += projectile->speed;
	check_collision(app, projectile_obj);
	if (projectile_obj && projectile->traveled > projectile->range)
	{
		object_set_for_deletion(app, projectile_obj);
		ft_printf("Deleted projectile! \n"); //test
	}
}
