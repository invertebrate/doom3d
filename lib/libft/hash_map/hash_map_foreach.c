/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_foreach.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:31:08 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/17 23:23:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"

void				hash_map_foreach(t_hash_table *table, void (*f)(void *val))
{
	t_hash_node	**curr;
	int			i;

	if (!table)
		return ;
	i = -1;
	while (++i < table->size)
	{
		curr = &table->list[i];
		while (*curr)
		{
			f(*curr);
			*curr = (*curr)->next;
		}
	}
}
