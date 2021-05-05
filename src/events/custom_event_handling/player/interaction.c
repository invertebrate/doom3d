/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:06:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:25:00 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_player_interact(t_doom3d *app)
{
	player_interact(app);
}

void	handle_player_jump(t_doom3d *app)
{
	player_jump(app);
}

void	handle_player_crouch(t_doom3d *app, t_bool is_crouching)
{
	player_crouch(app, is_crouching);
}

void	handle_player_toggle_flight(t_doom3d *app)
{
	app->player.can_fly = !app->player.can_fly;
}
