/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_foreach.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 20:31:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 23:15:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"

void	hash_map_foreach(t_hash_table *table,
			void (*f)(int64_t key, void *val, void *params1, void *params2),
			void *params1, void *params2)
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
			if (curr->val)
				f(curr->key, curr->val, params1, params2);
			curr = curr->next;
		}
	}
}

static void	add_counter(int64_t key, void *val,
				void *params1, void *params2)
{
	uint32_t		*counter;

	counter = params1;
	(void)params2;
	(void)key;
	(void)val;
	*counter += 1;
}

uint32_t	hash_map_get_count(t_hash_table *table)
{
	uint32_t	counter;

	counter = 0;
	hash_map_foreach(table, add_counter, &counter, NULL);
	return (counter);
}
