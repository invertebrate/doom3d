/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:23:49 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/28 01:47:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "tests.h"

int g_tests_run = 0;
t_test_state g_test_states[MAX_TESTS];

static void		all_tests(void)
{
	t_thread_pool	*pool;

	ft_printf("Hash_map tests:\n");
	OH_RUN_TEST(test_hash_map_create);
	OH_RUN_TEST(test_hash_map_add);
	OH_RUN_TEST(test_hash_map_get);
	OH_RUN_TEST(test_hash_map_delete);
	OH_RUN_TEST(test_hash_map_has_key);
	ft_printf("Thread pool tests: \n");
	OH_RUN_TEST(test_thread_pool_run);
	ft_printf("ft_memcpy tests:\n");
	OH_RUN_TEST(test_ft_memcpy);
	OH_RUN_TEST(test_ft_memcpy_ints);
	ft_printf("ft_memset tests:\n");
	OH_RUN_TEST(test_ft_memset);
	OH_RUN_TEST(test_ft_memset_ints);
	ft_printf("Radix Sort tests:\n");
	pool = thread_pool_create(4);
	OH_RUN_TEST_POOLED(test_radix_sort_simple, pool);
	OH_RUN_TEST_POOLED(test_radix_sort_randomized_small, pool);
	OH_RUN_TEST_POOLED(test_radix_sort_randomized_large, pool);
	OH_RUN_TEST_POOLED(test_radix_sort_simple_key_val, pool);
	OH_RUN_TEST_POOLED(test_radix_sort_large_key_val, pool);
	thread_pool_destroy(pool);
}

int				main(void)
{
	t_bool				success;
	int					failures;
	int					i;

	all_tests();
	success = true;
	failures = 0;
	i = -1;
	while (++i < g_tests_run)
	{
		if (!g_test_states[i].success)
		{
			success = false;
			failures++;
		}
	}
	ft_printf("===========\n");
	if (!success)
		ft_printf("%d out of %d TESTS FAILED\n", failures, g_tests_run);
	else
		ft_printf("ALL %d TESTS PASSED\n", g_tests_run);
	return (!success);
}
