/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_pickup_weapon.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:26:50 by ahakanen          #+#    #+#             */
/*   Updated: 2021/03/29 15:58:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		weapon_id_to_str(char *str, t_weapon_id weapon_id)
{
	if (weapon_id == weapon_shotgun)
		ft_sprintf(str, "Shotgun");
	else if (weapon_id == weapon_glock)
		ft_sprintf(str, "Glock");
	else if (weapon_id == weapon_rpg)
		ft_sprintf(str, "Rpg");
	else
		ft_sprintf(str, "Unknown");
}

void			inventory_pickup_weapon_object(t_doom3d *app,
					t_3d_object *weapon_drop_obj)
{
	t_weapon	*weapon;
	char		weapon_id[128];

	weapon = NULL;
	if (weapon_drop_obj->params_type == trigger_weapon_drop_shotgun)
		weapon = &app->weapons_data[weapon_shotgun];
	else if (weapon_drop_obj->params_type == trigger_weapon_drop_glock)
		weapon = &app->weapons_data[weapon_glock];
	else if (weapon_drop_obj->params_type == trigger_weapon_drop_rpg)
		weapon = &app->weapons_data[weapon_rpg];
	else if (weapon_drop_obj->params_type == trigger_item_jetpack)
		{
			app->player.can_fly = true;
			ft_printf("Picked up jetpack\n");
			doom3d_push_event(app, event_delete_object,
				weapon_drop_obj, NULL);
		}
	if (weapon)
	{
		weapon_id_to_str(weapon_id, weapon->id);
		app->player.weapons[weapon->id].ammo += weapon->ammo;
		ft_printf("Picked up %s %d ammo", weapon_id,
			app->player.weapons[weapon->id].ammo);
		doom3d_push_event(app, event_delete_object,
			weapon_drop_obj, NULL);
	}
}

void			inventory_pickup_key(t_doom3d *app, t_3d_object *key_obj)
{
	t_trigger	*key;

	key = key_obj->params;
	if (key->key_id < MAX_KEYS && app->player.keys[key->key_id] == false)
	{
		app->player.keys[key->key_id] = true;
		doom3d_push_event(app, event_delete_object,
			key_obj, NULL);
		ft_printf("picked up key %d\n", key->key_id);
	}
}