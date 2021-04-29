/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo     <veilo@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:12:44 by veilo             #+#    #+#             */
/*   Updated: 2021/04/29 18:30:23 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom3d.h"

uint32_t		arr_sum(uint32_t *arr, uint32_t length)
{
	uint32_t	i;
	uint32_t	result;

	result = 0;
	i = -1;
	while (++i < length)
	{
		result += arr[i];
	}
	return (result);
}