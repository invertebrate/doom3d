/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:21:49 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/29 18:32:02 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		npc_shoot_projectile(t_doom3d *app, t_vec3 origin, t_vec3 dir)
{
	t_projectile	projectile;
	t_vec3			rot;
	t_vec3			add;
	t_vec3			neworigin;
	t_vec3			newdir;

	ft_memset(&projectile, 0, sizeof(t_projectile));
	ft_memcpy(&projectile,
		&app->projectile_data[projectile_type_fireball],
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

static void	handle_atk_anim(t_doom3d *app, t_3d_object *npc_obj)
{
	uint32_t			new_time;
	t_npc				*npc;
	t_vec3				dist;
	t_anim_3d_instance	attack_inst;

	(void)app; //!ToDo: Remove from params if app is never needed...
	npc = npc_obj->params;
	init_anim_instance_attack(npc_obj, &attack_inst);// here init instance for attack animation, custom made function
	if (npc->animation_3d->current_anim_instance->active == false) //this prevents starting the clip before previous clip has ended
		anim_3d_clip_play(app, npc_obj, &attack_inst);//this plays the attack animation instance
	new_time = SDL_GetTicks();
	npc->atk_timer += new_time - npc->atk_start;
	if (npc->atk_timer > npc->atk_dur)
	{
		if (npc->atk_pattern[npc->atk_pattern_index] == action_melee_basic)
		{
			ml_vector3_sub(app->player.pos, npc_obj->position, dist);
			if (ml_vector3_mag(dist) < npc->atk_range)
				player_onhit(app, npc->atk_dmg);
		}
		if (npc->atk_pattern[npc->atk_pattern_index] == action_projectile_rpg)
		{
			npc_shoot_projectile(app, npc_obj->aabb.center, npc->dir);
			push_custom_event(app,
				event_effect_play, (void*)sf_monster_shoot, s_ini(0, 1, st_game,
				distance_vol(1, sound_mag(app->player.pos, npc_obj->position), -1)));
			if (app->is_debug)
				LOG_DEBUG("Npc %d shot projectile", npc_obj->id);
		}
		npc->state = state_attack;
	}
}

void		npc_update_state(t_doom3d *app, t_3d_object *npc_obj)
{
	t_npc	*npc;
	t_vec3	diff;
	float	dist;

	npc = npc_obj->params;
	ml_vector3_sub(npc_obj->aabb.center, app->player.aabb.center, diff);
	dist = ml_vector3_mag(diff);
	if (npc->state == state_idle)
	{
		if (dist < npc->vision_range &&
			npc_has_line_of_sight(app, npc_obj))
		{
			npc->state = state_attack;
			push_custom_event(app,
			event_effect_play, (void*)sf_monster_alert, s_ini(0, 1, st_game,
			distance_vol(0.8f, sound_mag(app->player.pos, npc_obj->position), -1)));
		}
		npc_get_dir_to_next_waypoint(app, npc_obj);
	}
	else if (npc->state == state_attack)
	{
		npc->atk_pattern_index++;
		if (npc->atk_pattern[npc->atk_pattern_index] == action_repeat)
			npc->atk_pattern_index = 0;
		if (dist >= npc->vision_range || !npc_has_line_of_sight(app, npc_obj))
		{
			npc->interest--;
			if (npc->interest < 0)
			{
				npc->atk_pattern_index = 0;
				npc->state = state_idle;
				ml_vector3_mul(npc->dir, 0, npc->dir);
				return ;
			}
		}
		else
			npc->interest = npc->max_interest;
		if (dist < npc->atk_range / 2
		&& npc->atk_pattern[npc->atk_pattern_index] == action_melee_basic)
		{
			npc->atk_timer = 0;
			npc->atk_start = SDL_GetTicks();
			npc->state = state_atk_anim;
		}
		if (npc->atk_pattern[npc->atk_pattern_index] == action_projectile_rpg &&
			npc_has_line_of_sight(app, npc_obj))
		{
			npc->atk_timer = 0;
			npc->atk_start = SDL_GetTicks();
			npc->state = state_atk_anim;
		}
		if (!npc_has_line_of_sight(app, npc_obj))
		{
			if (!npc->attack_path[0])
				npc_find_path(app, npc, npc_obj->position, app->player.pos);
			if (npc_get_dir_to_next_attack_waypoint(app, npc_obj))
				npc_find_path(app, npc, npc_obj->position, app->player.pos);
		}
		else
		{
			ft_memset(npc->attack_path, 0, sizeof(t_3d_object *) * MAX_PATH_NODE_NETWORK_SIZE);
			ml_vector3_normalize(diff, npc->dir);
			ml_vector3_mul(npc->dir, -npc->speed, npc->dir);
		}
	}
	else if (npc->state == state_atk_anim)
	{
		handle_atk_anim(app, npc_obj);
	}
	(void)handle_atk_anim;
	(void)app;
	(void)npc_obj;
}