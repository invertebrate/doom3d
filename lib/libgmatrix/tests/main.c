/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:19:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "tests.h"

int g_tests_run = 0;
t_test_state g_test_states[MAX_TESTS];

static void		all_tests(void)
{
	(void)g_tests_run;
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
