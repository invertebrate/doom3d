/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:53:38 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/14 16:17:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	projectile_on_hit(t_doom3d *app, t_3d_object *projectile_obj,
							t_3d_object *hit_obj)
{
	float			mag;
	int				damage;
	t_vec3			dist;
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	if (hit_obj && hit_obj->type == object_type_npc)
	{
		ml_vector3_sub(hit_obj->aabb.center, projectile_obj->aabb.center, dist);
		mag = ml_vector3_mag(dist);
		if (mag < projectile->radius)
		{
			damage = projectile->damage * (1 - (mag / projectile->radius));
			npc_trigger_onhit(app, hit_obj, damage);
		}
	}
	ml_vector3_sub(projectile_obj->aabb.center, app->player.aabb.center, dist);
	mag = ml_vector3_mag(dist);
	if (mag < projectile->radius)
	{
		damage = projectile->damage * (1 - (mag / projectile->radius));
		player_onhit(app, damage);
	}
}

void	projectile_update(t_doom3d *app, t_3d_object *projectile_obj)
{
	t_projectile	*projectile;
	t_vec3			add;

	projectile = projectile_obj->params;
	ml_vector3_mul(projectile->dir,
		projectile->speed * app->info.delta_time * CONST_SPEED, add);
	l3d_3d_object_translate(projectile_obj, add[0], add[1], add[2]);
	projectile->traveled += ml_vector3_mag(add);
	if (projectile_obj && projectile->traveled > projectile->range)
	{
		push_custom_event(app, event_object_delete,
			projectile_obj, NULL);
		return ;
	}
	projectile_handle_collision(app, projectile_obj);
}
