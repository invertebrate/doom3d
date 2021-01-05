/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_spawn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:35:21 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/05 16:51:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		place_npc_object_in_scene(t_doom3d *app, t_npc *npc)
{
	place_scene_object(app,
		(const char*[3]){npc->model_key, npc->texture_key, npc->normal_map_key},
		npc->pos);
	npc->obj = app->active_scene->objects[app->active_scene->num_objects - 1];
	l3d_3d_object_rotate(npc->obj, 0, npc->angle, 0);
}

static void		parse_type(t_doom3d *app, t_npc *npc, int type)
{
	if (type == npc_type_default)
		npc_default(app, npc);
}

/* spawn on position facing direction with given model */

void			npc_spawn(t_doom3d *app, t_vec3 pos, float angle, int type)
{
	static int	next_id;
	t_npc		npc;

	npc.is_deleted = false;
	npc.app = app;
	ml_vector3_copy(pos, npc.pos);
	npc.angle = angle;
	parse_type(app, &npc, type);
	npc.id = next_id;
	next_id++;
	place_npc_object_in_scene(app, &npc);
	if (app->active_scene->npc_list == NULL)
		app->active_scene->npc_list = ft_lstnew(&npc, sizeof(t_npc));
	else
		ft_lstappend(&(app->active_scene->npc_list),
			ft_lstnew(&npc, sizeof(t_npc)));
	ft_printf("Spawned npc, id = |%d|\n", npc.id); //test
}
