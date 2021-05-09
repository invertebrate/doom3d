/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_spawn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:35:21 by ahakanen          #+#    #+#             */
/*   Updated: 2021/05/07 14:54:53 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_3d_object	*place_npc_object_in_scene(t_doom3d *app, t_npc *npc,
												t_vec3 pos)
{
	t_3d_object	*obj;

	place_scene_object(app,
		(const char*[3]){npc->model_key, npc->texture_key, npc->normal_map_key},
		pos);
	obj = app->active_scene->objects[app->active_scene->last_object_index];
	obj->type = object_type_npc;
	l3d_3d_object_scale(obj, npc->model_scale, npc->model_scale,
		npc->model_scale);
	npc->parent = obj;
	l3d_3d_object_set_params(obj, npc, sizeof(t_npc), npc->type);
	if (npc->type == npc_type_monster01 || npc->type == npc_type_monster02
		|| npc->type == npc_type_monster01_a
		|| npc->type == npc_type_monster01_range
		|| npc->type == npc_type_boss)
	{
		obj->material->shading_opts = e_shading_standard;
		l3d_3d_object_rotate(obj, 0, 0, 180);
	}
	l3d_3d_object_rotate(obj, 0, npc->angle, 0);
	return (obj);
}

void	parse_npc_type(t_doom3d *app, t_npc *npc, int type)
{
	if (type == npc_type_monster01 || type == npc_type_monster01_a
		|| type == npc_type_boss)
	{
		npc_default(app, npc, NULL);
		if (npc->animation_3d != NULL)
		{
			free(npc->animation_3d);
			npc->animation_3d = NULL;
		}
	}
	if (type == npc_type_monster02 || type == npc_type_monster01_range)
	{
		npc_ranged(app, npc, NULL);
		if (npc->animation_3d != NULL)
		{
			free(npc->animation_3d);
			npc->animation_3d = NULL;
		}
	}
	npc_monster01(app, npc, type);
	if (type == npc_type_elevator)
		npc_elevator(app, npc, NULL);
	if (type == npc_type_crate)
		npc_crate(app, npc, NULL);
}

/*
** spawn on position facing direction with given model
*/

t_3d_object	*npc_spawn(t_doom3d *app, t_vec3 pos, float angle, int type)
{
	t_npc		npc;
	t_3d_object	*obj;

	ft_memset(&npc, 0, sizeof(t_npc));
	npc.angle = angle;
	parse_npc_type(app, &npc, type);
	obj = place_npc_object_in_scene(app, &npc, pos);
	if (npc.type == npc_type_monster01 || npc.type == npc_type_monster02
		|| npc.type == npc_type_monster01_a || npc.type
		== npc_type_monster01_range || npc.type == npc_type_boss)
		npc_animation_3d_init(app, npc.parent);
	if (npc.parent == NULL)
		LOG_INFO("default npc parent was null");
	LOG_INFO("Spawned npc, id = |%d|",
		app->active_scene->objects[app->active_scene->last_object_index]->id);
	return (obj);
}
