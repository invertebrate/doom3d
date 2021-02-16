/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 18:51:46 by ahakanen          #+#    #+#             */
/*   Updated: 2021/02/16 17:48:38 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		shoot_bullet_effect(t_doom3d *app,
					t_hit *hit, t_vec3 dir, const char *effect_key)
{
	t_3d_object 	*hit_effect;
	t_3d_object		*model;
	t_vec3			add;
	t_vec3			pos;
	float			scale;

	ml_vector3_mul(dir, -1 * 0.1 * app->unit_size, add);
	ml_vector3_add(hit->hit_point, add, pos);
	model = l3d_plane_create(NULL, NULL);
	hit_effect = place_procedural_temp_object(app, model,
		(const char*[2]){effect_key, NULL
	}, pos, (int32_t[2]){100, 0});
	scale = 0.1;
	l3d_3d_object_scale(hit_effect, scale, scale, scale);
	l3d_3d_object_rotate(hit_effect, app->player.rot_x,
		-app->player.rot_y, 90.0);
	l3d_3d_object_destroy(model);
}

static void		handle_shoot_hit(t_doom3d *app, t_hit *closest_triangle_hit,
					t_vec3 dir)
{
	if (app->player.equipped_weapon->id != weapon_fist &&
		closest_triangle_hit->triangle->parent->type != object_type_npc)
		shoot_bullet_effect(app, closest_triangle_hit, dir,
			"assets/textures/explosion1.bmp");
	if (closest_triangle_hit->triangle->parent->type == object_type_npc)
	{
		shoot_bullet_effect(app, closest_triangle_hit, dir,
			"assets/textures/blood.bmp");
		npc_trigger_onhit(app, closest_triangle_hit->triangle->parent,
						app->player.equipped_weapon->damage_per_hit);
	}
	if (closest_triangle_hit->triangle->parent->type == object_type_trigger)
	{
		trigger_activate(app, closest_triangle_hit->triangle->parent);
	}
}

static void		player_shoot_ray(t_doom3d *app, t_vec3 origin, t_vec3 dir)
{
	t_hits	*hits;
	t_hit	*closest_triangle_hit;
	t_vec3	dist;

	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, origin,
		dir, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit, -1);
		if (closest_triangle_hit != NULL)
		{
			ml_vector3_sub(closest_triangle_hit->hit_point, origin, dist);
			if (ml_vector3_mag(dist) <= app->player.equipped_weapon->range)
				handle_shoot_hit(app, closest_triangle_hit, dir);
		}
		l3d_delete_hits(&hits);
	}
}

void			place_projectile_object_in_scene(t_doom3d *app,
					t_projectile *projectile, t_vec3 origin, t_vec3 rot)
{
	t_3d_object *obj;

	place_scene_object(app,
		(const char*[3]){projectile->model_key, projectile->texture_key,
					projectile->normal_map_key}, origin);
	obj = app->active_scene->objects[app->active_scene->last_object_index];
	obj->type = object_type_projectile;
	l3d_3d_object_set_params(obj, projectile, sizeof(t_projectile),
		projectile->type);
	l3d_3d_object_rotate(obj, rot[0], rot[1], rot[2]);
	l3d_3d_object_scale(obj, 0.1, 0.1, 0.1);
	ft_printf("Spawned projectile, id = |%d|\n",
		app->active_scene->objects[app->active_scene->last_object_index]->id); //test
}

static void		player_shoot_projectile(t_doom3d *app, t_vec3 origin)
{
	t_projectile	projectile;
	t_vec3			rot;

	ft_memset(&projectile, 0, sizeof(t_projectile));
	ft_memcpy(&projectile,
		&app->projectile_data[app->player.equipped_weapon->projectile],
		sizeof(t_projectile));
	ml_vector3_copy(app->player.forward, projectile.dir);
	rot[0] = app->player.rot_x + 90;
	rot[1] = -app->player.rot_y;
	rot[2] = 90;
	ml_vector3_copy(rot, projectile.euler_angles);
	place_projectile_object_in_scene(app, &projectile, origin, rot);
}

static void		shoot_shotgun(t_doom3d *app, t_vec3 origin)
{
	t_vec3			add;
	t_vec3			target;
	t_vec3			add_sideways;
	t_vec3			add_upways;
	t_vec3			dir;
	int32_t			i;

	ml_vector3_mul(app->player.forward, app->unit_size, add);
	i = -1;
	while (++i < 6)
	{
		ml_vector3_add(app->player.pos, add, target);
		ml_vector3_mul(app->player.sideways,
			(0.15 * l3d_rand_d() - 0.075) * app->unit_size,
			add_sideways);
		ml_vector3_mul(app->player.up,
			(0.15 * l3d_rand_d() - 0.075) * app->unit_size,
			add_upways);
		ml_vector3_add(target, add_sideways, target);
		ml_vector3_add(target, add_upways, target);
		ml_vector3_sub(target, origin, dir);
		ml_vector3_normalize(dir, dir);
		player_shoot_ray(app, origin, dir);
	}
}

/*
** 	Clicking shoots right away. Else, fired according to fire rate
** // ToDo: Add various weapons & fire rates etc.
** // ToDo: Add bullet temp objects to hit surface
*/

void			player_shoot(t_doom3d *app, uint32_t curr_time)
{
	t_vec3			origin;
	t_vec3			add;
	static uint32_t	prev_shot_time;
	static uint32_t	prev_shot_weapon_id;

	if (prev_shot_weapon_id == app->player.equipped_weapon->id)
	{
		if (prev_shot_time != 0 && (float)(curr_time - prev_shot_time) / 1000.0 <
			(1.0 / app->player.equipped_weapon->fire_rate))
		return ;
	}
	if (app->player.equipped_weapon->ammo > 0)
		set_player_shoot_frame(app);
	else if (app->player.equipped_weapon->ammo == 0)
	{
		ft_printf("Out of ammo\n");
		set_player_default_frame(app);
		return ;
	}
	prev_shot_time = SDL_GetTicks();
	ml_vector3_mul(app->player.forward, NEAR_CLIP_DIST, add);
	ml_vector3_add(app->player.pos, add, origin);
	if (app->player.equipped_weapon->id == weapon_fist ||
		app->player.equipped_weapon->id == weapon_glock)
		player_shoot_ray(app, origin, app->player.forward);
	else if (app->player.equipped_weapon->id == weapon_rpg)
		player_shoot_projectile(app, origin);
	else if (app->player.equipped_weapon->id == weapon_shotgun)
		shoot_shotgun(app, origin);
	if (app->player.equipped_weapon->id != weapon_fist)
		app->player.equipped_weapon->ammo--;
	prev_shot_weapon_id = app->player.equipped_weapon->id;
}
