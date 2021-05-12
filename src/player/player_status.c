/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:53:53 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/12 08:40:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_onhit(t_doom3d *app, int damage)
{
	float	vol;

	app->player.hp -= damage;
	vol = (float)(damage) / (app->player.max_hp * 0.02f);
	if (vol > 1)
		vol = 1;
	push_custom_event(app,
		event_effect_play, (void*)sf_player_hurt, s_ini(0, 1, st_game, vol));
	if (app->player.hp <= 0)
	{
		push_custom_event(app, event_scene_change,
			(void *)scene_id_main_menu, NULL);
		notify_user(app, (t_notification){.message = "You died",
			.time = 6000, .type = notification_type_layer});
	}
}
