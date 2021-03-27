/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:23:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/28 01:43:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

const char		*test_hash_map_create(void);
const char		*test_hash_map_add(void);
const char		*test_hash_map_get(void);
const char		*test_hash_map_delete(void);
const char		*test_hash_map_has_key(void);
const char		*test_thread_pool_run(void);
const char		*test_ft_memcpy(void);
const char		*test_ft_memcpy_ints(void);
const char		*test_ft_memset_ints(void);
const char		*test_ft_memset(void);
const char		*test_radix_sort_simple(t_thread_pool *pool);
const char		*test_radix_sort_randomized_small(t_thread_pool *pool);
const char		*test_radix_sort_randomized_large(t_thread_pool *pool);
const char		*test_radix_sort_simple_key_val(t_thread_pool *pool);
const char		*test_radix_sort_large_key_val(t_thread_pool *pool);

#endif
