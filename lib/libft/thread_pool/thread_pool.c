/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:57:55 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/18 21:54:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_pool_utils.h"
#include "libft.h"

static void				thread_pool_worker(void *params)
{
	t_thread_pool	*thread_pool;

	thread_pool = (t_thread_pool*)params;
	while (thread_pool_worker_synchronize(thread_pool))
		;
	thread_pool->num_threads_alive--;
	pthread_cond_signal(&thread_pool->threads_vacant_all);
	pthread_mutex_unlock(&thread_pool->work_mutex);
}

t_thread_pool			*thread_pool_create(size_t num_threads)
{
	t_thread_pool	*thread_pool;
	pthread_t		thread;
	size_t			i;

	error_check(!(thread_pool = malloc(sizeof(*thread_pool))),
		"Failed to malloc thread pool");
	thread_pool->num_threads_working = 0;
	thread_pool->num_jobs = 0;
	thread_pool->stop = false;
	thread_pool->num_threads = num_threads == 0 ? 2 : num_threads;
	pthread_mutex_init(&thread_pool->work_mutex, NULL);
	pthread_cond_init(&thread_pool->work_to_process, NULL);
	pthread_cond_init(&thread_pool->threads_vacant_all, NULL);
	thread_pool->work_first = NULL;
	thread_pool->work_last = NULL;
	i = -1;
	while (++i < thread_pool->num_threads)
	{
		error_check(pthread_create(&thread, NULL, (void*)thread_pool_worker,
			thread_pool) != 0, "Failed create thread");
		error_check(pthread_detach(thread) != 0, "Failed to detach thread");
		thread_pool->num_threads_alive++;
	}
	return (thread_pool);
}

void					thread_pool_destroy(t_thread_pool *thread_pool)
{
	t_thread_work	*work;
	t_thread_work	*tmp_work;

	if (!thread_pool)
		return ;
	pthread_mutex_lock(&thread_pool->work_mutex);
	work = thread_pool->work_first;
	while (work != NULL)
	{
		tmp_work = work->next;
		thread_pool_work_destroy(work);
		work = tmp_work;
	}
	thread_pool->stop = true;
	pthread_cond_broadcast(&thread_pool->work_to_process);
	pthread_mutex_unlock(&thread_pool->work_mutex);
	thread_pool_wait(thread_pool);
	pthread_mutex_destroy(&thread_pool->work_mutex);
	pthread_cond_destroy(&thread_pool->work_to_process);
	pthread_cond_destroy(&thread_pool->threads_vacant_all);
	free(thread_pool);
	thread_pool = NULL;
}

t_bool					thread_pool_add_work(t_thread_pool *thread_pool,
							t_thread_work_func func, void *params)
{
	t_thread_work	*work;

	if (thread_pool == NULL)
		return (false);
	work = thread_pool_work_create(func, params);
	if (work == NULL)
		return (false);
	pthread_mutex_lock(&thread_pool->work_mutex);
	if (thread_pool->work_first == NULL)
	{
		thread_pool->work_first = work;
		thread_pool->work_last = thread_pool->work_first;
	}
	else
	{
		thread_pool->work_last->next = work;
		thread_pool->work_last = work;
	}
	thread_pool->num_jobs++;
	pthread_cond_broadcast(&thread_pool->work_to_process);
	pthread_mutex_unlock(&thread_pool->work_mutex);
	return (true);
}

void					thread_pool_wait(t_thread_pool *thread_pool)
{
	if (thread_pool == NULL)
		return ;
	pthread_mutex_lock(&thread_pool->work_mutex);
	while (thread_pool->num_jobs != 0)
	{
		if ((!thread_pool->stop && thread_pool->num_jobs != 0) ||
			(thread_pool->stop && thread_pool->num_threads_alive != 0))
			pthread_cond_wait(&thread_pool->threads_vacant_all,
				&thread_pool->work_mutex);
		else
			break ;
	}
	pthread_mutex_unlock(&thread_pool->work_mutex);
}
