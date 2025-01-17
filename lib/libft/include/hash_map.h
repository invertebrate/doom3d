/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:27:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 14:03:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MAP_H
# define HASH_MAP_H

# include <stdint.h>
# include <stdlib.h>
# include "t_bool.h"

typedef struct s_hash_node	t_hash_node;

struct s_hash_node
{
	int64_t		key;
	void		*val;
	t_hash_node	*next;
};

typedef struct s_hash_table
{
	int64_t		size;
	t_hash_node	**list;
}							t_hash_table;

/*
** Hash map / Dictionary / Hash table (whatever you want to call it).
** Usage:
** t_hash_table table = hash_map_create(50);
** t_rgb *color = malloc(sizeof(t_rgb));
** color->r = 5;
** color->g = 20;
** color->b = 25;
** hash_table_add(table, 15, (void*)color);
** t_rgb *ref = hash_map_get(table, 15);
** // NULL if not found
** Rest are convenience functions for clearing, deleting values & destroying
** hash table.
** Use delete_free if you also want to free the memory of values
** (if malloced)
*/

void						hash_map_delete(t_hash_table *table, int64_t key);
void						hash_map_delete_free(t_hash_table *table,
								int64_t key);
void						hash_map_clear(t_hash_table *table);
void						hash_map_clear_free(t_hash_table *table);
void						hash_map_destroy(t_hash_table *table);
void						hash_map_destroy_free(t_hash_table *table);
t_hash_table				*hash_map_create(size_t size);
int64_t						hash_map_hash(t_hash_table *table, int64_t key);
void						*hash_map_get(t_hash_table *table, int64_t key);
void						hash_map_add(t_hash_table *table, int64_t key,
								void *val);
t_bool						hash_map_has_key(t_hash_table *table, int64_t key);
void						hash_map_foreach(t_hash_table *table,
								void (*f)(int64_t key, void *val,
									void *params1, void *params2),
								void *params1, void *params2);
uint32_t					hash_map_get_count(t_hash_table *table);

#endif
