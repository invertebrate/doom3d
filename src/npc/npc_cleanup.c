/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:32:20 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/04 16:44:28 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	delete_npc(void *npc, size_t size)
{
  (void)size;
  if (npc != NULL)
    free(npc);
}

void		npc_cleanup(t_doom3d *app)
{
    ft_lstdel(app->npc_list, delete_npc);
}