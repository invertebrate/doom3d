/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_reload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:58:53 by ahakanen          #+#    #+#             */
/*   Updated: 2021/04/02 15:35:33 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_reload(t_doom3d *app)
{
	if (app->player.equipped_weapon->clip < 
		app->player.equipped_weapon->clip_size &&
		app->player.equipped_weapon->clip != 
		app->player.equipped_weapon->ammo)
	{
		set_player_reload_frame(app);
		if (app->player.equipped_weapon->ammo < 
				app->player.equipped_weapon->clip_size)
			app->player.equipped_weapon->clip = 
									app->player.equipped_weapon->ammo;
		else
			app->player.equipped_weapon->clip = 
									app->player.equipped_weapon->clip_size;
	}
}