/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:47:28 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/05 19:48:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_controller_init(t_doom3d *app)
{
	app->active_scene->npc_update_timer = 0;
	app->active_scene->npc_list = NULL;
}

void	npc_controller(t_doom3d *app)
{
	static uint32_t	old_time;
	uint32_t		new_time;

	if (app->active_scene->is_paused ||
		app->active_scene->scene_id != scene_id_main_game)
		return ;
	new_time = SDL_GetTicks();
	if (!old_time)
		old_time = 0;
	app->active_scene->npc_update_timer += new_time - old_time;
	if (app->active_scene->npc_update_timer > 250)
	{
		app->active_scene->npc_update_timer -= 250;
		ft_lstiter(app->active_scene->npc_list, npc_update);
		old_time = new_time;
	}
	ft_lstiter(app->active_scene->npc_list, npc_execute_behavior);
}