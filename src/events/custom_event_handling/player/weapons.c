/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 00:08:47 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 03:20:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** ToDo: Might add logging here, or open the functions up for logging purposes
*/

void		handle_player_shoot(t_doom3d *app)
{
	player_shoot(app, SDL_GetTicks());
}

void		handle_player_reload(t_doom3d *app)
{
	player_reload(app);
}

void		handle_player_weapon_equip(t_doom3d *app, t_weapon_id weapon)
{
	weapon_equip(app, weapon);
}
