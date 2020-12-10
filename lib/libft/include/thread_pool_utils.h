/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:47:50 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/18 21:45:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_POOL_UTILS_H
# define THREAD_POOL_UTILS_H

# include "thread_pool.h"

t_thread_work	*thread_pool_work_create(t_thread_work_func work_func,
					void *params);
void			thread_pool_work_destroy(t_thread_work *work);
t_thread_work	*thread_pool_work_get(t_thread_pool *thread_pool);
t_bool			thread_pool_worker_synchronize(t_thread_pool *thread_pool);

#endif
