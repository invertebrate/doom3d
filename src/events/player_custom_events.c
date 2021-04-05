/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_custom_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 02:40:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 03:17:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		player_custom_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_player_rotate)
		ft_sprintf(str, "PlayerRotate");
	else if (code == event_player_shoot)
		ft_sprintf(str, "PlayerShoot");
	else if (code == event_player_reload)
		ft_sprintf(str, "PlayerReload");
	else if (code == event_player_crouch)
		ft_sprintf(str, "PlayerCrouch");
	else if (code == event_player_weapon_equip)
		ft_sprintf(str, "PlayerEquipWeapon");
	else if (code == event_player_move)
		ft_sprintf(str, "PlayerMove");
	else if (code == event_player_jump)
		ft_sprintf(str, "PlayerJump");
	else if (code == event_player_toggle_flight)
		ft_sprintf(str, "PlayerToggleFlight");
}

void		register_player_custom_events(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_player_rotate,
		(void*)handle_player_rotate);
	hash_map_add(app->custom_event_handles, event_player_shoot,
		(void*)handle_player_shoot);
	hash_map_add(app->custom_event_handles, event_player_reload,
		(void*)handle_player_reload);
	hash_map_add(app->custom_event_handles, event_player_weapon_equip,
		(void*)handle_player_weapon_equip);
	hash_map_add(app->custom_event_handles, event_player_crouch,
		(void*)handle_player_crouch);
	hash_map_add(app->custom_event_handles, event_player_move,
		(void*)handle_player_move);
	hash_map_add(app->custom_event_handles, event_player_jump,
		(void*)handle_player_jump);
	hash_map_add(app->custom_event_handles, event_player_toggle_flight,
		(void*)handle_player_toggle_flight);
}
