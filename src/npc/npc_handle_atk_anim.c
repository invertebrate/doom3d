/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_handle_atk_anim.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:27:37 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/03 17:45:31 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	npc_shoot_projectile(t_doom3d *app, t_vec3 origin, t_vec3 dir,
									int type)
{
	t_projectile	projectile;
	t_vec3			rot;
	t_vec3			add;
	t_vec3			neworigin;
	t_vec3			newdir;

	ft_memset(&newdir, 0, sizeof(newdir));
	ft_memset(&projectile, 0, sizeof(t_projectile));
	ft_memcpy(&projectile,
		&app->projectile_data[type],
		sizeof(t_projectile));
	rot[0] = 0;
	rot[1] = 0;
	rot[2] = 0;
	ml_vector3_copy(rot, projectile.euler_angles);
	ml_vector3_normalize(dir, newdir);
	ml_vector3_copy(newdir, projectile.dir);
	ml_vector3_mul(newdir, app->unit_size * 3, add);
	ml_vector3_add(origin, add, neworigin);
	place_projectile_object_in_scene(app, &projectile, neworigin, rot);
}

static void	handle_attack(t_doom3d *app, t_3d_object *npc_obj, t_npc *npc)
{
	t_vec3	dist;

	if (npc->atk_pattern[npc->atk_pattern_index] == action_melee_basic)
	{
		ml_vector3_sub(app->player.pos, npc_obj->position, dist);
		if (ml_vector3_mag(dist) < npc->atk_range)
			player_onhit(app, npc->atk_dmg);
	}
	if (npc->atk_pattern[npc->atk_pattern_index] == action_projectile_rpg)
	{
		if (npc->type == npc_type_monster01_range)
			npc_shoot_projectile(app, npc_obj->aabb.center, npc->dir,
				projectile_type_fireball_green);
		else
			npc_shoot_projectile(app, npc_obj->aabb.center, npc->dir,
				projectile_type_fireball);
		push_custom_event(app,
			event_effect_play, (void*)sf_monster_shoot, s_ini(0, 1, st_game,
				distance_vol(1, sound_mag(app->player.pos,
						npc_obj->position), -1)));
		if (app->is_debug)
			LOG_DEBUG("Npc %d shot projectile", npc_obj->id);
	}
}

void	handle_atk_anim(t_doom3d *app, t_3d_object *npc_obj)
{
	uint32_t			new_time;
	t_npc				*npc;
	t_anim_3d_instance	attack_inst;

	npc = npc_obj->params;
	init_anim_instance_attack(npc_obj, &attack_inst);
	if (npc->animation_3d->current_anim_instance->active == false)
		anim_3d_clip_play(app, npc_obj, &attack_inst);
	new_time = SDL_GetTicks();
	npc->atk_timer += new_time - npc->atk_start;
	if (npc->atk_timer > npc->atk_dur)
	{
		handle_attack(app, npc_obj, npc);
		npc->state = state_attack;
	}
}
