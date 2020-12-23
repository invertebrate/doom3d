/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:21:49 by ahakanen          #+#    #+#             */
/*   Updated: 2020/12/22 19:51:41 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	npc_update(t_npc *npc)
{
	/*
	check state of npc
	*/
	if (npc->state == IDLE)
	{
		/*
		DO IDLE THINGS WITH THIS NPC
		*/
	}
	else if (npc->state == ATTACK)
	{
		/*
		DO ATTACK THINGS WITH THIS NPC
		*/
	}
}