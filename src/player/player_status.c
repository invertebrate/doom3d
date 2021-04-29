/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 12:53:53 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/13 13:10:31 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_onhit(t_doom3d *app, int damage)
{
	float	vol;

	app->player.hp -= damage;
	vol = app->player.max_hp * 0.01f * damage;
	vol = vol > 1 ? 1 : vol;
	// if (app->player.hp <= 0)
	// {
	// 	ft_printf("You died!\n"); //test
	// }
	// ft_printf("player hit for %d damage! current hp: %d\n",
		// damage, app->player.hp); //test
	push_custom_event(app,
		event_effect_play, (void*)sf_player_hurt, s_ini(0, 1, st_game, vol));
	(void)app;
}