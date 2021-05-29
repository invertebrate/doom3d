/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:53:38 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/30 01:19:27 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	handle_lights(t_doom3d *app, t_3d_object *projectile_obj,
							t_3d_object *hit_obj)
{
	float			mag;
	t_vec3			dist;
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	ml_vector3_sub(hit_obj->aabb.center, projectile_obj->aabb.center, dist);
	mag = ml_vector3_mag(dist);
	if (mag < projectile->radius)
		check_light_breakable(app, hit_obj);
}

static void	splash_damage_npc(t_doom3d *app, t_3d_object *projectile_obj,
							t_3d_object *hit_obj)
{
	float			mag;
	int				damage;
	t_vec3			dist;
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	ml_vector3_sub(hit_obj->aabb.center, projectile_obj->aabb.center, dist);
	mag = ml_vector3_mag(dist);
	if (mag < projectile->radius)
	{
		damage = projectile->damage * (1 - (mag / projectile->radius));
		npc_trigger_onhit(app, hit_obj, damage);
	}
}

static void	handle_splash_damage(t_doom3d *app, t_3d_object *projectile_obj,
							t_3d_object *hit_obj)
{
	int32_t			i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		hit_obj = app->active_scene->objects[i];
		if (!hit_obj)
			continue ;
		if (object_is_ignored(app, hit_obj))
			continue ;
		if (hit_obj->type == object_type_light)
			handle_lights(app, projectile_obj, hit_obj);
		if (hit_obj->type == object_type_npc)
			splash_damage_npc(app, projectile_obj, hit_obj);
	}
	player_splash_damage(app, projectile_obj);
}

void	projectile_on_hit(t_doom3d *app, t_3d_object *projectile_obj,
							t_3d_object *hit_obj)
{
	float			mag;
	int				damage;
	t_vec3			dist;
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	if (hit_obj && hit_obj->type == object_type_light)
		handle_lights(app, projectile_obj, hit_obj);
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
	handle_splash_damage(app, projectile_obj, hit_obj);
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
