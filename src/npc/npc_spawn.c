/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_spawn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:35:21 by ahakanen          #+#    #+#             */
/*   Updated: 2021/02/15 11:53:09 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		place_npc_object_in_scene(t_doom3d *app, t_npc *npc, t_vec3 pos)
{
	t_3d_object *obj;

	place_scene_object(app,
		(const char*[3]){npc->model_key, npc->texture_key, npc->normal_map_key},
		pos);
	obj = app->active_scene->objects[app->active_scene->last_object_index];
	obj->type = object_type_npc;
	l3d_3d_object_scale(obj, npc->model_scale, npc->model_scale, npc->model_scale);
	npc->parent = obj;
	l3d_3d_object_set_params(obj, npc, sizeof(t_npc), npc->type);
	if (npc->type == npc_type_default)
		l3d_3d_object_rotate(obj, 0, 180, 180);//hardcoded for specific model
	l3d_3d_object_rotate(obj, 0, npc->angle, 0);
}

void			parse_npc_type(t_doom3d *app, t_npc *npc, int type)
{
	if (type == npc_type_default)
	{
		npc_default(app, npc, NULL);
		if (npc->animation_3d != NULL)
		{
			free(npc->animation_3d);
			npc->animation_3d = NULL;//this so that rendering doesnt crash because in editor
			//doesnt have animation frames for objects
		}
	}
	if (type == npc_type_ranged)
	{
		npc_ranged(app, npc, NULL);
		if (npc->animation_3d != NULL)
		{
			free(npc->animation_3d);
			npc->animation_3d = NULL;//this so that rendering doesnt crash because in editor
			//doesnt have animation frames for objects
		}
	}
	if (type == npc_type_elevator)
	{
		npc_elevator(app, npc, NULL);
	}
}

/*
** spawn on position facing direction with given model
*/

void			npc_spawn(t_doom3d *app, t_vec3 pos, float angle, int type)
{
	t_npc		npc;

	ft_memset(&npc, 0, sizeof(t_npc));
	npc.angle = angle;
	parse_npc_type(app, &npc, type);
	place_npc_object_in_scene(app, &npc, pos);//mallocs and copies data from npc, sets params
	ft_printf("Spawned npc, id = |%d|\n",
		app->active_scene->objects[app->active_scene->last_object_index]->id); //test
}
