/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:27:15 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/16 19:23:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MAP_H
# define HASH_MAP_H

# include <stdlib.h>
# include "t_bool.h"

typedef struct s_hash_node	t_hash_node;

struct						s_hash_node
{
	int			key;
	void		*val;
	t_hash_node	*next;
};

typedef struct				s_hash_table
{
	int			size;
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

void						hash_map_delete(t_hash_table *table, int key);
void						hash_map_delete_free(t_hash_table *table, int key);
void						hash_map_clear(t_hash_table *table);
void						hash_map_clear_free(t_hash_table *table);
void						hash_map_destroy(t_hash_table *table);
void						hash_map_destroy_free(t_hash_table *table);
t_hash_table				*hash_map_create(int size);
int							hash_map_hash(t_hash_table *table, int key);
void						*hash_map_get(t_hash_table *table, int key);
void						hash_map_add(t_hash_table *table, int key,
							void *val);
t_bool						hash_map_has_key(t_hash_table *table, int key);

#endif
