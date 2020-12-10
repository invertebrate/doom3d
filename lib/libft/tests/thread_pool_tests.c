/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool_tests.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:59:30 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/18 21:27:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "libft.h"

static void		work_f(void *params)
{
	int		*val;

	val = params;
	*val += 1000;
}

const char		*test_thread_pool_run(void)
{
	size_t			num_items;
	t_thread_pool	*pool;
	int				*vals;
	size_t			i;
	int				sum;

	num_items = 1000;
	pool = thread_pool_create(4);
	OH_ASSERT("Failed to create thread pool", pool != NULL);
	vals = malloc(sizeof(int) * num_items);
	i = -1;
	while (++i < num_items)
	{
		vals[i] = i;
		thread_pool_add_work(pool, work_f, vals + i);
	}
	thread_pool_wait(pool);
	i = -1;
	sum = 0;
	while (++i < num_items)
		sum += vals[i];
	OH_ASSERT("TP Failed", sum == (int)i * ((int)i - 1) / 2 + (int)i * 1000);
	free(vals);
	thread_pool_destroy(pool);
	return (0);
}
