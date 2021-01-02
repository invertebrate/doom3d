/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/02 16:08:13 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_default(t_doom3d *app, t_npc *npc)
{
	npc->speed = app->unit_size / 32;
	npc->rot_speed = 10;
	npc->state = 0;
	npc->hp = 100;
	npc->model = hash_map_get(app->active_scene->models,
		(int64_t)DEFAULT_MODEL);
	if (!npc->model)
	{
		ft_dprintf(2, "No existing model file (%s) given to place npc."
			"Add it in scene_assets.c\n",
			DEFAULT_MODEL);
		return ;
	}
	npc->obj = l3d_object_instantiate(npc->model, app->unit_size, false);
	npc->texture = hash_map_get(app->active_scene->textures,
		(int64_t)DEFAULT_TEXTURE);
	if (npc->texture)
	{
		l3d_object_set_texture(npc->obj, npc->texture);
		hash_map_add(app->active_scene->object_textures, npc->obj->id,
			DEFAULT_TEXTURE);
	}
	l3d_3d_object_translate(npc->obj, npc->pos[0], npc->pos[1], npc->pos[2]);
	l3d_3d_object_rotate(npc->obj, 0, npc->angle, 0);
	app->active_scene->objects[app->active_scene->num_objects++] = npc->obj;
}