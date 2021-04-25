/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   performance_counter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:31:46 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 17:31:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

uint64_t		performance_counter_start(void)
{
	return (SDL_GetPerformanceCounter());
}

/*
** Usage:
** uint64_t	start = performance_counter_start();
** // Do stuff here
** performance_counter_end(start, "What I did?", 10.0); // where
** // 10.0 is to only print out a result when time diff is > 10ms
** // At 0.0, result is always printed
*/

void			performance_counter_end(uint64_t start_time,
					char *task_name, float delta_limit)
{
	float			delta_time;

	delta_time = (float)(SDL_GetPerformanceCounter() -
		start_time) * 1000.0 /
		(float)SDL_GetPerformanceFrequency();
	if (delta_limit == 0.0 || delta_time > delta_limit)
		LOG_TRACE("%s: Profiler time: %f", task_name, delta_time);
}
