/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:53:35 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 21:35:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"
#include "ft_printf.h"

/*
** Creates a hash table of given size.
** Each element in the table is set as NULL
*/

t_hash_table	*hash_map_create(size_t size)
{
	t_hash_table	*table;
	int64_t			i;

	table = ft_calloc(sizeof(t_hash_table));
	error_check(!table, "Failed to malloc hash table");
	table->size = size;
	error_check(!(table->list = ft_calloc(sizeof(t_hash_node *) * size)),
		"Failed to malloc hash table list");
	i = -1;
	while (++i < (int64_t)size)
		table->list[i] = NULL;
	return (table);
}

/*
** Hashing function used to quickly access areas inside the hash table
*/

int64_t	hash_map_hash(t_hash_table *table, int64_t key)
{
	if (key < (int64_t)0)
		return (-(key % table->size));
	return (key % table->size);
}

/*
** Add an element void* to the hash table. If a node with given key is found
** that value is replaced with inputted value.
** Else a new node is added.
*/

void	hash_map_add(t_hash_table *table, int64_t key, void *val)
{
	int64_t		pos;
	t_hash_node	*list;
	t_hash_node	*temp;
	t_hash_node	*new_node;

	if (!table)
		return ;
	pos = hash_map_hash(table, key);
	list = table->list[pos];
	temp = list;
	while (temp)
	{
		if (temp->key == key)
		{
			temp->val = val;
			return ;
		}
		temp = temp->next;
	}
	error_check(!(new_node = ft_calloc(sizeof(t_hash_node))),
		"Failed to malloc new node to hash table");
	new_node->key = key;
	new_node->val = val;
	new_node->next = list;
	table->list[pos] = new_node;
}

/*
** Retrieve a value from the hash table. If value is not found, return NULL.
*/

void	*hash_map_get(t_hash_table *table, int64_t key)
{
	t_hash_node	*temp;

	if (!table)
		return (NULL);
	temp = table->list[hash_map_hash(table, key)];
	while (temp)
	{
		if (temp->key == key)
			return (temp->val);
		temp = temp->next;
	}
	return (NULL);
}

/*
** Retrieve a value from the hash table. If value is not found, return NULL.
*/

t_bool	hash_map_has_key(t_hash_table *table, int64_t key)
{
	t_hash_node	*temp;

	if (!table)
		return (false);
	temp = table->list[hash_map_hash(table, key)];
	while (temp)
	{
		if (temp->key == key)
			return (true);
		temp = temp->next;
	}
	return (false);
}
