/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:48:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/31 03:03:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	update_npc_object(t_doom3d *app, t_3d_object *obj,
					t_bool is_npc_update)
{
	if (((t_npc *)obj->params)->animation_3d != NULL)
		anim_3d_frame_update(app, ((t_npc *)obj->params)->animation_3d);
	if (is_npc_update && ((t_npc *)obj->params)->state != state_death_anim)
		npc_update_state(app, obj);
	if (((t_npc *)obj->params)->state != state_death_anim)
		npc_execute_behavior(app, obj);
}

static void	update_trigger_object(t_doom3d *app, t_3d_object *obj)
{
	if (l3d_aabb_collides(&app->player.aabb, &obj->aabb))
	{
		if (obj->params_type == trigger_player_end)
			finish_level(app, obj);
		else if (obj->params_type == trigger_weapon_drop_shotgun
			|| obj->params_type == trigger_weapon_drop_pistol
			|| obj->params_type == trigger_weapon_drop_rpg
			|| obj->params_type == trigger_item_jetpack)
			inventory_pickup_weapon_object(app, obj);
		else if (obj->params_type == trigger_item_key)
			inventory_pickup_key(app, obj);
		else if (obj->params_type == trigger_item_medkit)
			inventory_pickup_medkit(app, obj);
		else if (obj->params_type == trigger_hurtbox)
			player_onhit(app, HURT_DMG);
		else if (obj->params_type == trigger_jukebox)
			handle_jukebox(app, obj);
		else if (obj->params_type == trigger_musicbox)
			handle_musicbox(app, obj);
	}
}

/*
** The texture tests are for sprite object effects, if object has textures
** 
*/

static void	update_object_by_type(t_doom3d *app, t_3d_object *obj,
					t_bool is_npc_update)
{
	if (object_has_forces(obj))
	{
		update_object_physics_state(app, obj);
		update_object_forces(app, obj);
	}
	if (obj->type == object_type_npc)
		update_npc_object(app, obj, is_npc_update);
	else if (obj->type == object_type_projectile)
		projectile_update(app, obj);
	else if (obj->type == object_type_trigger)
		update_trigger_object(app, obj);
	if (obj->material->texture
		&& ft_strequ(obj->material->texture->filename,
			"assets/textures/reactor_diffuse.bmp"))
		reactor_explosion_effect(app, obj);
	else if (obj->material->texture
		&& ft_strequ(obj->material->texture->filename,
			"assets/textures/hologram_diffuse.bmp"))
		hologram_effect(app, obj);
}

static void	update_in_game_objects(t_doom3d *app)
{
	int32_t			i;
	t_bool			is_npc_update;
	t_3d_object		*obj;

	is_npc_update = should_update_npc_state(app);
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects
		+ app->active_scene->num_free_indices))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		if (object_is_ignored(app, obj))
			continue ;
		update_object_by_type(app, obj, is_npc_update);
		update_object_light_sources(app, obj);
	}
	update_temp_objects_light_sources(app);
	l3d_temp_objects_update_time(&app->active_scene->temp_objects,
		app->info.delta_time);
}

/*
** Updates objects every frame. In addition applies gravity / physics
** to objects & player. Handles object deletion
** Also keeps scene structures up to date (triangle tree)
*/

void	update_objects(t_doom3d *app)
{
	if (!(app->active_scene->scene_id == scene_id_main_game
			|| app->active_scene->scene_id == scene_id_editor3d))
		return ;
	if (app->active_scene->scene_id == scene_id_editor3d)
		update_editor_light_sources(app);
	else if (!app->active_scene->is_paused
		&& app->active_scene->scene_id == scene_id_main_game)
		update_in_game_objects(app);
	delete_objects_set_for_deletion(app);
	active_scene_update_after_objects(app);
}
