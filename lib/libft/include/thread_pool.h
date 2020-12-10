/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:47:10 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/18 21:52:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_H
# define THREAD_POOL_H

# include <pthread.h>
# include <stdlib.h>
# include "t_bool.h"

typedef void					(*t_thread_work_func)(void *params);

typedef struct s_thread_work	t_thread_work;

struct							s_thread_work
{
	t_thread_work_func	work_func;
	void				*params;
	t_thread_work		*next;
};

typedef struct					s_thread_pool
{
	t_thread_work		*work_first;
	t_thread_work		*work_last;
	pthread_mutex_t		work_mutex;
	pthread_cond_t		work_to_process;
	pthread_cond_t		threads_vacant_all;
	size_t				num_threads;
	volatile size_t		num_threads_working;
	volatile size_t		num_threads_alive;
	volatile size_t		num_jobs;
	volatile t_bool		stop;
}								t_thread_pool;

t_thread_pool					*thread_pool_create(size_t num_threads);
void							thread_pool_destroy(t_thread_pool *thread_pool);
t_bool							thread_pool_add_work(t_thread_pool *thread_pool,
									t_thread_work_func function, void *params);
void							thread_pool_wait(t_thread_pool *thread_pool);

#endif
