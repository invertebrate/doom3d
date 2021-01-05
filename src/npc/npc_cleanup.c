/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:32:20 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/05 17:17:42 by ohakola          ###   ########.fr       */
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

void		npc_delete_one(t_npc *npc_to_delete)
{
	npc_to_delete->is_deleted = true;
}

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
		}
		else
			curr = &(*curr)->next;
	}
}