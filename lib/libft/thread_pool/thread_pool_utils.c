/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:16:05 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:16:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool.h"
#include "libft.h"

t_thread_work			*thread_pool_work_create(t_thread_work_func work_func,
							void *params)
{
	t_thread_work	*work;

	error_check(work_func == NULL, "Work func for work was NULL");
	error_check(!(work = malloc(sizeof(*work))), "Failed to malloc work");
	work->work_func = work_func;
	work->params = params;
	work->next = NULL;
	return (work);
}

void					thread_pool_work_destroy(t_thread_work *work)
{
	if (work == NULL)
		return ;
	free(work);
	work = NULL;
}

t_thread_work			*thread_pool_work_get(t_thread_pool *thread_pool)
{
	t_thread_work	*work;

	if (thread_pool == NULL)
		return (NULL);
	work = thread_pool->work_first;
	if (work == NULL)
		return (NULL);
	if (work->next == NULL)
	{
		thread_pool->work_first = NULL;
		thread_pool->work_last = NULL;
	}
	else
		thread_pool->work_first = work->next;
	return (work);
}

static t_bool			thread_pool_signal_end(t_thread_pool *tp)
{
	if (!tp->stop && tp->num_threads_working == 0 && tp->num_jobs == 0)
	{
		pthread_cond_signal(&tp->threads_vacant_all);
		return (true);
	}
	return (false);
}

t_bool					thread_pool_worker_synchronize(t_thread_pool *tp)
{
	t_thread_work	*work;

	pthread_mutex_lock(&tp->work_mutex);
	while (!tp->stop && tp->num_jobs == 0)
		pthread_cond_wait(&tp->work_to_process, &tp->work_mutex);
	if (tp->stop)
		return (false);
	if ((work = thread_pool_work_get(tp)) == NULL)
	{
		thread_pool_signal_end(tp);
		pthread_mutex_unlock(&tp->work_mutex);
		return (true);
	}
	tp->num_threads_working++;
	pthread_mutex_unlock(&tp->work_mutex);
	work->work_func(work->params);
	thread_pool_work_destroy(work);
	pthread_mutex_lock(&tp->work_mutex);
	tp->num_jobs--;
	tp->num_threads_working--;
	thread_pool_signal_end(tp);
	pthread_mutex_unlock(&tp->work_mutex);
	return (true);
}
