/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:47:28 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/04 14:11:05 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_controller_init(t_doom3d *app)
{
	app->npc_update_timer = 0;
	app->npc_list = NULL;
}

void	npc_controller(t_doom3d *app)
{
	static uint32_t	old_time;
	uint32_t		new_time;

	new_time = SDL_GetTicks();
	if (!old_time)
		old_time = 0;
	app->npc_update_timer += new_time - old_time;
	if (app->npc_update_timer > 250)
	{
		app->npc_update_timer -= 250;
		ft_lstiter(app->npc_list, npc_update);
		old_time = new_time;
	}
	ft_lstiter(app->npc_list, npc_execute_behavior);
}