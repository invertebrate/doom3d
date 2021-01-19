/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:53:38 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/19 16:21:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		projectile_on_hit(t_doom3d *app,
					t_3d_object *projectile_obj, t_3d_object *hit_obj,
					t_player *player)
{
	float			mag;
	int				damage;
	t_vec3			dist;
	t_projectile	*projectile;

	projectile = projectile_obj->params;
	if (hit_obj)
	{
		ml_vector3_sub(hit_obj->position, projectile_obj->position, dist);
		if (hit_obj->type == object_type_npc &&
			(mag = ml_vector3_mag(dist)) < projectile->radius)
		{
			damage = projectile->damage /
				(1 + (mag / (app->unit_size * 10))) + 0.5 * projectile->damage;
			npc_trigger_onhit(app, hit_obj, damage);
		}
	}
	else if (player)
	{
		ml_vector3_sub(hit_obj->position, player->pos, dist);
		if ((mag = ml_vector3_mag(dist)) < projectile->radius)
		{
			damage = projectile->damage /
				(1 + (mag / (app->unit_size * 10))) + 0.5 * projectile->damage;
			player_onhit(app, damage);
		}
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
		if (!obj)
			continue ;
		ml_vector3_sub(obj->position, projectile_obj->position, dist);
		if (ml_vector3_mag(dist) < 10 * app->unit_size
				&& obj->type != object_type_projectile
				&& obj->type != object_type_trigger)
			if (l3d_aabb_collides(&obj->aabb, &projectile_obj->aabb))
			{
				projectile_explode(app, projectile_obj);
				object_set_for_deletion(app, projectile_obj);
				projectile_on_hit(app, projectile_obj, obj, NULL);
				return ;
			}
	}
	if (l3d_aabb_collides(&app->player.aabb, &projectile_obj->aabb))
	{
		projectile_explode(app, projectile_obj);
		object_set_for_deletion(app, projectile_obj);
		projectile_on_hit(app, projectile_obj, NULL, &app->player);
	}
}

void			projectile_update(t_doom3d *app, t_3d_object *projectile_obj)
{
	t_projectile	*projectile;
	t_vec3			pos_new;

	projectile = projectile_obj->params;
	ml_vector3_add(projectile_obj->position, projectile->dir, pos_new);
	ml_vector3_copy(pos_new, projectile_obj->position);
	l3d_3d_object_translate(projectile_obj, projectile->dir[0], projectile->dir[1], projectile->dir[2]);
	projectile->traveled += projectile->speed;
	projectile_handle_collision(app, projectile_obj);
	if (projectile_obj && projectile->traveled > projectile->range)
	{
		object_set_for_deletion(app, projectile_obj);
		ft_printf("Deleted projectile! \n"); //test
	}
}
