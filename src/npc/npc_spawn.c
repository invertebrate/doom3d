/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_spawn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:35:21 by ahakanen          #+#    #+#             */
/*   Updated: 2020/12/30 18:31:32 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	parse_type(t_doom3d *app, t_npc *npc, int type)
{
	if (type == 0)
		npc_default(app, npc);
}

/* spawn on position facing direction with given model */

void	npc_spawn(t_doom3d *app, t_vec3 pos, float angle, int type)
{
	static int	next_id;
	t_npc		npc;

	npc.app = app;
	ml_vector3_copy(pos, npc.pos);
	npc.angle = angle;
	parse_type(app, &npc, type);
	npc.id = next_id;
	next_id++;
	if (app->npc_list == NULL)
		app->npc_list = ft_lstnew(&npc, sizeof(t_npc));
	else
		ft_lstappend(&(app->npc_list), ft_lstnew(&npc, sizeof(t_npc)));
	ft_printf("Spawned npc, id = |%d|\n", npc.id); //test
}
