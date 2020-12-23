/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 16:47:28 by ahakanen          #+#    #+#             */
/*   Updated: 2020/12/22 19:51:37 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

t_list	*npc_controller_init(void)
{
	t_list	*npc_list;

	npc_list = ft_lstnew(NULL, 0);
	return (npc_list);
}

void	npc_controller(t_list *npc_list, float time)
{
	if (enoughtimepassed)
		ft_lstiter(npc_list, npc_update);
	ft_lstiter(npc_list, TODO_EXECUTEBEHAVIOR);
}