/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_pickup_weapon.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:26:50 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/26 16:52:33 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	weapon_id_to_str(char *str, t_weapon_id weapon_id)
{
	if (weapon_id == weapon_shotgun)
		ft_sprintf(str, "Shotgun");
	else if (weapon_id == weapon_pistol)
		ft_sprintf(str, "pistol");
	else if (weapon_id == weapon_rpg)
		ft_sprintf(str, "Rpg");
	else
		ft_sprintf(str, "Unknown");
}

static void	give_jetpack(t_doom3d *app, t_3d_object *jetpack_obj)
{
	app->player.can_fly = true;
	if (app->settings.is_debug)
		LOG_DEBUG("Picked up Jetpack");
	push_custom_event(app, event_object_delete,
		jetpack_obj, NULL);
	jetpack_obj->params_type = trigger_type_disabled;
}

void	inventory_pickup_weapon_object(t_doom3d *app,
					t_3d_object *weapon_drop_obj)
{
	t_weapon	*weapon;
	char		weapon_id[128];

	weapon = NULL;
	if (weapon_drop_obj->params_type == trigger_weapon_drop_shotgun)
		weapon = &app->weapons_data[weapon_shotgun];
	else if (weapon_drop_obj->params_type == trigger_weapon_drop_pistol)
		weapon = &app->weapons_data[weapon_pistol];
	else if (weapon_drop_obj->params_type == trigger_weapon_drop_rpg)
		weapon = &app->weapons_data[weapon_rpg];
	else if (weapon_drop_obj->params_type == trigger_item_jetpack)
		give_jetpack(app, weapon_drop_obj);
	if (weapon)
	{
		weapon_id_to_str(weapon_id, weapon->id);
		app->player.weapons[weapon->id].ammo += weapon->clip_size * 4;
		if (app->settings.is_debug)
			LOG_DEBUG("Picked up %s %d ammo", weapon_id,
				app->player.weapons[weapon->id].ammo);
		push_custom_event(app, event_object_delete,
			weapon_drop_obj, NULL);
		weapon_drop_obj->params_type = trigger_type_disabled;
	}
	push_custom_event(app,
		event_effect_play, (void*)sf_gun_rel, s_ini(0, 1, st_game, 1.0));
}

void	inventory_pickup_key(t_doom3d *app, t_3d_object *key_obj)
{
	t_trigger	*key;

	key = key_obj->params;
	if (key->key_id < MAX_KEYS && app->player.keys[key->key_id] == false)
	{
		app->player.keys[key->key_id] = true;
		push_custom_event(app, event_object_delete,
			key_obj, NULL);
		push_custom_event(app,
			event_effect_play, (void*)sf_pickup, s_ini(0, 1, st_game, 1.0));
		if (app->settings.is_debug)
			LOG_DEBUG("Picked up key %d", key->key_id);
		key_obj->params_type = trigger_type_disabled;
	}
}

void	inventory_pickup_medkit(t_doom3d *app, t_3d_object *medkit_obj)
{
	if (app->player.hp < app->player.max_hp)
	{
		if (app->settings.is_hard)
			app->player.hp += app->player.max_hp * 0.25;
		else
			app->player.hp = app->player.max_hp;
		if (app->player.hp > app->player.max_hp)
			app->player.hp = app->player.max_hp;
		push_custom_event(app, event_object_delete,
			medkit_obj, NULL);
		push_custom_event(app,
			event_effect_play, (void*)sf_pickup, s_ini(0, 1, st_game, 1.0));
		if (app->settings.is_debug)
			LOG_DEBUG("Picked up medkit");
		medkit_obj->params_type = trigger_type_disabled;
	}
}
