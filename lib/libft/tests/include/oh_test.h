/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oh_test.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:15:20 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:03:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OH_TEST_H
# define OH_TEST_H

# include "libft.h"
# include "test_state.h"

# define MAX_TESTS 1024

/*
** Modified version of
** http://www.jera.com/techinfo/jtns/jtn002.html
** using a TestState struct to better output results.
*/

# define OH_ASSERT(message, test) { if (!(test)) return message; }
# define OH_RUN_TEST(test) { update_test_state(test); }
# define OH_RUN_TEST_POOLED(t, p) { update_test_state_with_pool(t, p); }

extern int			g_tests_run;
extern t_test_state	g_test_states[MAX_TESTS];

#endif
