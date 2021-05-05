/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:58:24 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:02:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"

t_test_state	test_state_create(t_bool success, const char *result, int id)
{
	t_test_state	state;

	state = (t_test_state){.success = success, .result = result, .id = id};
	return (state);
}

void	update_test_state_with_pool(const char *(*t)(
					t_thread_pool *p), t_thread_pool *p)
{
	const char		*message;
	t_test_state	state;
	t_bool			is_success;

	message = t(p);
	g_tests_run++;
	if (message)
		is_success = false;
	else
		is_success = true;
	state = test_state_create(is_success,
			message, g_tests_run - 1);
	g_test_states[g_tests_run - 1] = state;
	if (state.success)
		ft_printf(" test: %d: Success\n");
	else
		ft_printf(" test: %d: %s\n", state.id, state.result);
}

void	update_test_state(const char *(*test)(void))
{
	const char		*message;
	t_test_state	state;
	t_bool			is_success;

	message = test();
	g_tests_run++;
	if (message)
		is_success = false;
	else
		is_success = true;
	state = test_state_create(is_success,
			message, g_tests_run - 1);
	g_test_states[g_tests_run - 1] = state;
	if (state.success)
		ft_printf(" test: %d: Success\n");
	else
		ft_printf(" test: %d: %s\n", state.id, state.result);
}
