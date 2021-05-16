/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_foreach.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:31:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 21:15:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"

void	hash_map_foreach(t_hash_table *table,
			void (*f)(int64_t key, void *val, void *params), void *params)
{
	t_hash_node	*curr;
	int64_t		i;

	if (!table)
		return ;
	i = -1;
	while (++i < table->size)
	{
		curr = table->list[i];
		while (curr)
		{
			f(curr->key, curr->val, params);
			curr = curr->next;
		}
	}
}
