/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:43:04 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 18:48:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	npc_shoot_projectile(t_doom3d *app, t_vec3 origin, t_vec3 dir,
									int type)
{
	t_projectile	projectile;
	t_vec3			add;
	t_vec3			neworigin;
	t_vec3			newdir;

	ft_memset(&newdir, 0, sizeof(newdir));
	ft_memset(&projectile, 0, sizeof(t_projectile));
	ft_memcpy(&projectile,
		&app->projectile_data[type],
		sizeof(t_projectile));
	ml_vector3_normalize(dir, newdir);
	ml_vector3_copy(newdir, projectile.dir);
	ml_vector3_mul(newdir, app->unit_size * 3, add);
	ml_vector3_add(origin, add, neworigin);
	place_npc_projectile_in_scene(app, &projectile, neworigin);
}

static void	handle_projectile(t_doom3d *app, t_3d_object *npc_obj, t_npc *npc)
{
	t_vec3	dir;

	ml_vector3_copy(npc->dir, dir);
	ml_vector3_mul(dir, -1, dir);
	if (npc->type == npc_type_monster01_range)
		npc_shoot_projectile(app, npc_obj->aabb.center, dir,
			projectile_type_fireball_green);
	else if (npc->type == npc_type_boss)
		npc_shoot_projectile(app, npc_obj->aabb.center, dir,
			projectile_type_fireball_purple);
	else
		npc_shoot_projectile(app, npc_obj->aabb.center, dir,
			projectile_type_fireball);
	push_custom_event(app,
		event_effect_play, (void *)sf_monster_shoot, s_ini(0, 1, st_game,
			distance_vol(1, sound_mag(app->player.pos,
					npc_obj->position), -1)));
}

void	handle_npc_projectile_shoot(t_doom3d *app, t_3d_object *npc_obj)
{
	t_npc	*npc;

	if (!npc_obj)
		return ;
	npc = npc_obj->params;
	handle_projectile(app, npc_obj, npc);
}
