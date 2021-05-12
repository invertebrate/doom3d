/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_placement1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:50:31 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 15:50:17 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	placement_notification(t_doom3d *app, char *txt)
{
	notify_user(app, (t_notification){
		.message = txt,
		.type = notification_type_info, .time = 2000});
}

static t_3d_object	*place_start_or_end(t_doom3d *app,
						t_trigger_type trigger_type)
{
	t_3d_object		*trigger;
	t_3d_object		*old_trigger;

	trigger = NULL;
	if (trigger_type == trigger_player_start)
	{
		old_trigger = find_one_object_by_type(app,
				object_type_trigger, trigger_player_start);
		if (old_trigger)
			push_custom_event(app, event_object_delete, old_trigger, NULL);
		trigger = place_player_start(app);
		placement_notification(app,
			"Placing Player Start (Deleted old if had one)!");
	}
	else if (trigger_type == trigger_player_end)
	{
		old_trigger = find_one_object_by_type(app,
				object_type_trigger, trigger_player_end);
		if (old_trigger)
			push_custom_event(app, event_object_delete, old_trigger, NULL);
		trigger = place_player_end(app);
		placement_notification(app,
			"Placing Player End (Deleted old if had one)!");
	}
	return (trigger);
}

static t_3d_object	*place_weapon_drop(t_doom3d *app,
						t_trigger_type trigger_type)
{
	t_3d_object		*trigger;

	trigger = NULL;
	if (trigger_type == trigger_weapon_drop_shotgun)
	{
		trigger = place_drop_shotgun(app);
		placement_notification(app, "Placing shotgun trigger");
	}
	else if (trigger_type == trigger_weapon_drop_pistol)
	{
		trigger = place_drop_pistol(app);
		placement_notification(app, "Placing pistol trigger");
	}
	else if (trigger_type == trigger_weapon_drop_rpg)
	{
		trigger = place_drop_rpg(app);
		placement_notification(app, "Placing RPG trigger");
	}
	return (trigger);
}

static t_3d_object	*place_item_drop(t_doom3d *app,
						t_trigger_type trigger_type)
{
	t_3d_object		*trigger;

	trigger = NULL;
	if (trigger_type == trigger_item_jetpack)
	{
		trigger = place_drop_jetpack(app);
		placement_notification(app, "Placing jetpack trigger");
	}
	else if (trigger_type == trigger_item_medkit)
	{
		trigger = place_drop_medkit(app);
		placement_notification(app, "Placing medkit trigger");
	}
	else if (trigger_type == trigger_item_key)
	{
		trigger = place_drop_key(app);
		placement_notification(app, "Placing key trigger");
	}
	return (trigger);
}

/*
** Place a trigger object in editor
*/

t_3d_object	*editor_place_trigger_object(t_doom3d *app,
									t_trigger_type trigger_type)
{
	t_3d_object		*trigger;

	trigger = NULL;
	if (trigger_type == trigger_player_start
		|| trigger_type == trigger_player_end)
		trigger = place_start_or_end(app, trigger_type);
	else if (trigger_type == trigger_weapon_drop_shotgun
		|| trigger_type == trigger_weapon_drop_pistol
		|| trigger_type == trigger_weapon_drop_rpg)
		trigger = place_weapon_drop(app, trigger_type);
	else if (trigger_type == trigger_item_jetpack
		|| trigger_type == trigger_item_medkit
		|| trigger_type == trigger_item_key)
		trigger = place_item_drop(app, trigger_type);
	else if (trigger_type == trigger_elevator_switch)
		trigger = place_elevator_switch(app);
	else if (trigger_type == trigger_door_switch)
		trigger = place_elevator_switch_timer(app);
	else if (trigger_type == trigger_hurtbox)
		trigger = place_hurt_box(app);
	else if (trigger_type == trigger_jukebox)
		trigger = place_jukebox(app);
	else if (trigger_type == trigger_musicbox)
		trigger = place_musicbox(app);
	return (trigger);
}
