/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 00:08:47 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:25:08 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_player_shoot(t_doom3d *app)
{
	player_shoot(app, SDL_GetTicks());
}

void	handle_player_reload(t_doom3d *app)
{
	player_reload(app);
}

void	handle_player_weapon_equip(t_doom3d *app, t_weapon_id weapon)
{
	if (player_animation_state(app) != anim_state_default)
		return ;
	weapon_equip(app, weapon);
}
