/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:32:20 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/05 19:13:49 by ohakola          ###   ########.fr       */
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

/*
** Clean all npcs e.g when scene changes or app is stopped
** Note that npc->obj are cleaned up by another function since they belong
** under the scene.
*/

void		npc_cleanup(t_doom3d *app)
{
	if (app->active_scene->npc_list == NULL)
		return ;
	ft_lstdel(&app->active_scene->npc_list, delete_npc);
	app->active_scene->npc_list = NULL;
	app->active_scene->num_npcs = 0;
}

/*
** Set npcs to be deleted
*/

void		npc_set_to_be_deleted(t_npc *npc_to_delete)
{
	npc_to_delete->is_deleted = true;
}

/*
** Called in main loop in doom3d.c to handle npcs deletions in the beginning
** of the loop.
*/

void		handle_npc_deletions(t_doom3d *app)
{
	t_list		**curr;
	t_list		*temp;
	t_npc		*npc;

	curr = &app->active_scene->npc_list;
	while (*curr)
	{
		temp = *curr;
		npc = (t_npc*)((*curr)->content);
		if (npc && npc->is_deleted == true)
		{
			*curr = temp->next;
			set_object_for_deletion(app, npc->obj);
			delete_npc(npc, 0);
			free(temp);
			temp = NULL;
			app->active_scene->num_npcs--;
		}
		else
			curr = &(*curr)->next;
	}
}