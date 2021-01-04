/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/04 16:27:35 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_default(t_doom3d *app, t_npc *npc)
{
	npc->speed = app->unit_size / 32;
	npc->rot_speed = 10;
	npc->state = 0;
	npc->hp = 100;
	npc->atk_range = app->unit_size * 5;
	npc->atk_dur = 500;
	npc->vision_range = app->unit_size * 10;
	place_scene_object(app, (const char*[3]){DEFAULT_MODEL, DEFAULT_TEXTURE,
		NULL}, (t_vec3){npc->pos[0], npc->pos[1], npc->pos[2]});
	npc->obj = app->active_scene->objects[app->active_scene->num_objects - 1];
}