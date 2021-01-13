/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 12:08:04 by ahakanen          #+#    #+#             */
/*   Updated: 2021/01/11 13:29:56 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_default(t_doom3d *app, t_npc *npc)
{
	npc->type = npc_type_default;
	npc->speed = app->unit_size / 32;
	npc->rot_speed = 10;
	npc->state = 0;
	npc->hp = 100;
	npc->atk_range = app->unit_size * 5;
	npc->atk_dur = 500;
	npc->vision_range = app->unit_size * 10;
	npc->model_key = NPC_DEFAULT_MODEL;
	npc->texture_key = NPC_DEFAULT_TEXTURE;
	npc->normal_map_key = NPC_DEFAULT_NORMM;
}