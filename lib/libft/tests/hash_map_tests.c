/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_tests.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 19:39:09 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/16 19:08:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "libft.h"

const char		*test_hash_map_create(void)
{
	t_hash_table	*hash_map;
	int				size;

	size = 128;
	hash_map = NULL;
	hash_map = hash_map_create(size);
	OH_ASSERT("Hash map wasn't created", hash_map != NULL);
	OH_ASSERT("Hash map size is wrong", hash_map->size == size);
	hash_map_destroy_free(hash_map);
	return (0);
}

const char		*test_hash_map_add(void)
{
	t_hash_table	*hash_map;
	int				size;
	int				key;
	int				hashed_key;
	const char		*result_str;

	size = 128;
	hash_map = hash_map_create(size);
	key = (int)"okko";
	hashed_key = hash_map_hash(hash_map, key);
	hash_map_add(hash_map, key, (void*)"an aristocrat");
	result_str = (char*)hash_map->list[hashed_key]->val;
	OH_ASSERT("Hash map add is not correct",
		ft_strequ(result_str, "an aristocrat"));
	hash_map_destroy(hash_map);
	return (0);
}

const char		*test_hash_map_get(void)
{
	t_hash_table	*hash_map;
	int				size;
	int				key;

	size = 128;
	hash_map = hash_map_create(size);
	key = (int)"okko";
	hash_map_add(hash_map, key, (void*)"an aristocrat");
	OH_ASSERT("Hash map get is not correct",
		ft_strequ((char*)hash_map_get(hash_map, key), "an aristocrat"));
	key = (int)"marsupilami";
	hash_map_add(hash_map, key, (void*)"an automat");
	OH_ASSERT("Hash map get is not correct",
		ft_strequ((char*)hash_map_get(hash_map, key), "an automat"));
	hash_map_destroy(hash_map);
	return (0);
}

const char		*test_hash_map_delete(void)
{
	t_hash_table			*hash_map;
	int						size;
	int						key1;
	int						key2;

	size = 128;
	hash_map = hash_map_create(size);
	key1 = 1;
	hash_map_add(hash_map, key1, ft_strdup("an aristocrat"));
	key2 = 2;
	hash_map_add(hash_map, key2, ft_strdup("an automat"));
	hash_map_delete_free(hash_map, key1);
	OH_ASSERT("Hash map delete1 is not correct",
		hash_map_get(hash_map, key1) == NULL);
	hash_map_delete_free(hash_map, key2);
	OH_ASSERT("Hash map delete2 is not correct",
		hash_map_get(hash_map, key2) == NULL);
	hash_map_destroy_free(hash_map);
	return (0);
}

const char		*test_hash_map_has_key(void)
{
	t_hash_table	*hash_map;
	int				size;
	int				key;
	int				hashed_key;

	size = 128;
	hash_map = hash_map_create(size);
	key = (int)"okko";
	hashed_key = hash_map_hash(hash_map, key);
	hash_map_add(hash_map, key, (void*)"an aristocrat");
	OH_ASSERT("Hash has key is not correct",
		hash_map_has_key(hash_map, key) == true);
	OH_ASSERT("Hash has key is not correct",
		hash_map_has_key(hash_map, (int)"lol") == false);
	hash_map_destroy(hash_map);
	return (0);
}
