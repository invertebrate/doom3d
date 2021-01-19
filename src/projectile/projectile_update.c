/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:53:38 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/19 17:03:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		projectile_explode_effect(t_doom3d *app,
					t_3d_object *projectile_obj)
{
	(void)app;
	(void)projectile_obj;	
}

static void		projectile_on_hit(t_doom3d *app,
					t_3d_object *projectile_obj, t_3d_object *hit_obj)
{
	float			mag;
	int				damage;
	t_vec3			dist;
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	if (hit_obj && hit_obj->type == object_type_npc)
	{
		ml_vector3_sub(hit_obj->position, projectile_obj->position, dist);
		if ((mag = ml_vector3_mag(dist)) < projectile->radius)
		{
			damage = projectile->damage /
				(1 + (mag / (app->unit_size * 10))) + 0.5 * projectile->damage;
			npc_trigger_onhit(app, hit_obj, damage);
		}
	}
	ml_vector3_sub(hit_obj->position, app->player.pos, dist);
	if ((mag = ml_vector3_mag(dist)) < projectile->radius)
	{
		damage = projectile->damage /
			(1 + (mag / (app->unit_size * 10))) + 0.5 * projectile->damage;
		player_onhit(app, damage);
	}
}

static void		projectile_handle_collision(t_doom3d *app,
					t_3d_object *projectile_obj)
{
	t_vec3		dist;
	int			i;
	t_3d_object	*obj;


	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
							app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (!obj || obj->type == object_type_projectile ||
				obj->type == object_type_trigger)
			continue ;
		ml_vector3_sub(obj->position, projectile_obj->position, dist);
		if (ml_vector3_mag(dist) <
			((t_projectile*)projectile_obj->params)->radius * 2 &&
			l3d_aabb_collides(&obj->aabb, &projectile_obj->aabb))
		{
			projectile_explode_effect(app, projectile_obj);
			object_set_for_deletion(app, projectile_obj);
			projectile_on_hit(app, projectile_obj, obj);
			return ;
		}
	}
}

void			projectile_update(t_doom3d *app, t_3d_object *projectile_obj)
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
		object_set_for_deletion(app, projectile_obj);
		return ;
	}
	projectile_handle_collision(app, projectile_obj);
}
