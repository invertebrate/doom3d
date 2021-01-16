/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:47:01 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/16 17:46:35 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	player_jump(t_doom3d *app)
{
	if (player_is_grounded(app))
	{
		app->player.velocity[1] += app->player.jump_force;
	}
}