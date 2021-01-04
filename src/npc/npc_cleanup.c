/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:32:20 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/04 21:09:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	delete_npc(void *npc, size_t size)
{
	(void)size;
	if (npc != NULL)
	{
		ft_printf("Deleting npc %d\n", ((t_npc*)npc)->id);
		free(npc);
		npc = NULL;
	}
}

void		npc_cleanup(t_doom3d *app)
{
	if (app->active_scene->npc_list == NULL)
		return ;
	ft_lstdel(&app->active_scene->npc_list, delete_npc);
	app->active_scene->npc_list = NULL;
}