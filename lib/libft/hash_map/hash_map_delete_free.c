/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_delete_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:25:46 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/21 16:38:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"
#include "ft_printf.h"

/*
** Delete a t_hash_node in a hash map if found.
** Also frees value. If value has not been malloced, a crash may occur.
*/

void				hash_map_delete_free(t_hash_table *table, int key)
{
	int			pos;
	t_hash_node	**curr;
	t_hash_node	*temp;

	if (!table)
		return ;
	pos = hash_map_hash(table, key);
	curr = &table->list[pos];
	while (*curr)
	{
		temp = *curr;
		if (temp->key == key)
		{
			*curr = temp->next;
			free(temp->val);
			free(temp);
			temp = NULL;
			break ;
		}
		else
			curr = &(*curr)->next;
	}
}

/*
** Clear elements inside hashmap freeing also table values' memory.
** If value(s) has not been malloced, a crash may occur.
*/

void				hash_map_clear_free(t_hash_table *table)
{
	int			i;
	t_hash_node	*temp;
	t_hash_node	**curr;

	if (!table)
		return ;
	i = -1;
	while (++i < table->size)
	{
		curr = &table->list[i];
		while (*curr)
		{
			temp = *curr;
			*curr = temp->next;
			free(temp->val);
			free(temp);
			temp = NULL;
		}
		table->list[i] = NULL;
	}
}

/*
** Destroy entire hash table freeing its memory.
** Also frees values. If value(s) has not been malloced, a crash may occur.
*/

void				hash_map_destroy_free(t_hash_table *table)
{
	if (!table)
		return ;
	hash_map_clear_free(table);
	free(table->list);
	free(table);
}
