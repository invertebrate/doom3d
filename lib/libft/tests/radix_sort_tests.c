/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_tests.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:06:27 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 15:58:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "radix_sort_utils.h"
#include "utils.h"

const char	*test_radix_sort_simple(t_thread_pool *pool)
{
	uint32_t		array[8];
	uint32_t		check_array[8];
	size_t			array_size;

	array[0] = 1115;
	array[1] = 80000;
	array[2] = 322410;
	array[3] = 1;
	array[4] = 112;
	array[5] = 1163515;
	array[6] = 2222;
	array[7] = 12345;
	array_size = 8;
	copy_array(check_array, array, array_size);
	sort_check_array(check_array, array_size);
	radix_sort(pool, array, array_size);
	OH_ASSERT("Radix sort simple sorted wrong",
		arrays_match(check_array, array, array_size));
	return (0);
}

const char	*test_radix_sort_randomized_small(t_thread_pool *pool)
{
	uint32_t		array[16];
	uint32_t		check_array[16];
	size_t			array_size;

	array_size = 16;
	rand_array(array, array_size);
	copy_array(check_array, array, array_size);
	sort_check_array(check_array, array_size);
	radix_sort(pool, array, array_size);
	OH_ASSERT("Radix sort randomized small sorted wrong",
		arrays_match(check_array, array, array_size));
	return (0);
}

const char	*test_radix_sort_randomized_large(t_thread_pool *pool)
{
	uint32_t		array[131072];
	uint32_t		check_array[131072];
	size_t			array_size;

	array_size = 131072;
	rand_array(array, array_size);
	copy_array(check_array, array, array_size);
	sort_check_array(check_array, array_size);
	radix_sort(pool, array, array_size);
	OH_ASSERT("Radix sort randomized large sorted wrong",
		arrays_match(check_array, array, array_size));
	return (0);
}

/*
** Sets values to be 0-5 indices, so checking against check array is easy
** the values (indices, thus unique) should not be same for sorted array
** just make sure the size is even
*/

const char	*test_radix_sort_simple_key_val(t_thread_pool *pool)
{
	uint32_t		key_vals[2][8];
	uint32_t		*key_vals_to_sort[2];
	size_t			i;

	key_vals[0][0] = 5;
	key_vals[0][1] = 4;
	key_vals[0][2] = 3;
	key_vals[0][3] = 2;
	key_vals[0][4] = 1;
	key_vals[0][5] = 0;
	i = -1;
	while (++i < 6)
		key_vals[1][i] = i;
	key_vals_to_sort[0] = key_vals[0];
	key_vals_to_sort[1] = key_vals[1];
	radix_sort_key_val(pool, key_vals_to_sort, 6);
	i = -1;
	while (++i < 6)
		OH_ASSERT("Radix sort simple key_val sorted wrong",
			key_vals_to_sort[1][i] == 6 - 1 - i);
	return (0);
}

const char	*test_radix_sort_large_key_val(t_thread_pool *pool)
{
	uint32_t		key_vals[2][12345];
	uint32_t		*key_vals_to_sort[2];
	size_t			i;

	i = -1;
	while (++i < 12345)
	{
		key_vals[0][i] = 12345 - 1 - i;
		key_vals[1][i] = i;
	}
	key_vals_to_sort[0] = key_vals[0];
	key_vals_to_sort[1] = key_vals[1];
	radix_sort_key_val(pool, key_vals_to_sort, 12345);
	i = -1;
	while (++i < 12345)
		OH_ASSERT("Radix sort simple key_val sorted wrong",
			key_vals_to_sort[1][i] == 12345 - 1 - i);
	return (0);
}
