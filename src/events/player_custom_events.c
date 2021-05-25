/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_custom_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 02:40:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/25 20:44:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_custom_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_player_rotate)
		ft_sprintf(str, "event_player_rotate");
	else if (code == event_player_shoot_projectile)
		ft_sprintf(str, "event_player_shoot");
	else if (code == event_player_reload)
		ft_sprintf(str, "event_player_reload");
	else if (code == event_player_crouch)
		ft_sprintf(str, "event_player_crouch");
	else if (code == event_player_weapon_equip)
		ft_sprintf(str, "event_player_weapon_equip");
	else if (code == event_player_move)
		ft_sprintf(str, "event_player_move");
	else if (code == event_player_jump)
		ft_sprintf(str, "event_player_jump");
	else if (code == event_player_toggle_flight)
		ft_sprintf(str, "event_player_toggle_flight");
	else if (code == event_third_person_zoom)
		ft_sprintf(str, "event_third_person_zoom");
	else if (code == event_set_difficulty)
		ft_sprintf(str, "event_set_difficulty");
}

void	register_player_custom_events(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_player_rotate,
		(void *)handle_player_rotate);
	hash_map_add(app->custom_event_handles, event_player_shoot_projectile,
		(void *)handle_player_shoot_projectile);
	hash_map_add(app->custom_event_handles, event_player_reload,
		(void *)handle_player_reload);
	hash_map_add(app->custom_event_handles, event_player_interact,
		(void *)handle_player_interact);
	hash_map_add(app->custom_event_handles, event_player_weapon_equip,
		(void *)handle_player_weapon_equip);
	hash_map_add(app->custom_event_handles, event_player_crouch,
		(void *)handle_player_crouch);
	hash_map_add(app->custom_event_handles, event_player_move,
		(void *)handle_player_move);
	hash_map_add(app->custom_event_handles, event_player_jump,
		(void *)handle_player_jump);
	hash_map_add(app->custom_event_handles, event_player_toggle_flight,
		(void *)handle_player_toggle_flight);
	hash_map_add(app->custom_event_handles, event_third_person_zoom,
		(void *)handle_third_person_zoom);
	hash_map_add(app->custom_event_handles, event_set_difficulty,
		(void *)handle_set_difficulty);
}
